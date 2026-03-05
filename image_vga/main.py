#!/usr/bin/env python3
from __future__ import annotations
import argparse
from collections import Counter
from PIL import Image

W, H = 160, 120

# --- Color packing: RGB888 -> RGB332 (8-bit) (cabe en 9 bits raw_c) ---
def rgb_to_rgb332(r: int, g: int, b: int) -> int:
    r3 = (r * 7 + 127) // 255
    g3 = (g * 7 + 127) // 255
    b2 = (b * 3 + 127) // 255
    return (r3 << 5) | (g3 << 2) | b2  # 0..255

# Si quieres RGB333 (9-bit), usa esto y comenta rgb332:
# def rgb_to_rgb333(r:int,g:int,b:int)->int:
#     r3 = (r * 7 + 127) // 255
#     g3 = (g * 7 + 127) // 255
#     b3 = (b * 7 + 127) // 255
#     return (r3 << 6) | (g3 << 3) | b3  # 0..511


def quantize_image(img: Image.Image, colors: int, dither: bool) -> Image.Image:
    """
    Cuantiza con paleta adaptativa a 'colors' colores.
    Luego lo devuelve en RGB (para leer pixeles).
    """
    img = img.convert("RGB")
    # convert a palette image
    img_p = img.convert(
        "P",
        palette=Image.ADAPTIVE,
        colors=colors,
        dither=Image.FLOYDSTEINBERG if dither else Image.NONE
    )
    return img_p.convert("RGB")


def build_tile_grid(img: Image.Image, tile: int) -> list[list[int]]:
    """
    Convierte imagen (160x120) a grid (H/tile x W/tile),
    donde cada celda tiene el color dominante del tile.
    """
    pix = img.load()
    gw = W // tile
    gh = H // tile
    grid = [[0 for _ in range(gw)] for _ in range(gh)]

    for ty in range(gh):
        for tx in range(gw):
            colors = []
            x0 = tx * tile
            y0 = ty * tile
            for y in range(y0, y0 + tile):
                for x in range(x0, x0 + tile):
                    r, g, b = pix[x, y]
                    c = rgb_to_rgb332(r, g, b)
                    colors.append(c)
            # color dominante (mode)
            grid[ty][tx] = Counter(colors).most_common(1)[0][0]
    return grid


def greedy_rectangles(grid: list[list[int]]) -> list[tuple[int,int,int,int,int]]:
    """
    Encuentra rectángulos máximos (greedy) de mismo color en el grid de tiles.
    Devuelve rects en coordenadas de CELDAS: (tx,ty,tw,th,color)
    """
    gh = len(grid)
    gw = len(grid[0]) if gh else 0
    used = [[False]*gw for _ in range(gh)]
    rects = []

    for y in range(gh):
        for x in range(gw):
            if used[y][x]:
                continue
            c = grid[y][x]

            # expand width
            w = 1
            while x+w < gw and (not used[y][x+w]) and grid[y][x+w] == c:
                w += 1

            # expand height as far as all cells in width match and unused
            h = 1
            while y+h < gh:
                ok = True
                for xx in range(x, x+w):
                    if used[y+h][xx] or grid[y+h][xx] != c:
                        ok = False
                        break
                if not ok:
                    break
                h += 1

            # mark used
            for yy in range(y, y+h):
                for xx in range(x, x+w):
                    used[yy][xx] = True

            rects.append((x, y, w, h, c))
    return rects


def split_rect_pixels(x: int, y: int, w: int, h: int, c: int, maxw: int, maxh: int):
    """
    Split para asegurar w<=maxw y h<=maxh (por 4 bits => 15).
    """
    out = []
    yy = y
    hh = h
    while hh > 0:
        hch = min(hh, maxh)
        xx = x
        ww = w
        while ww > 0:
            wch = min(ww, maxw)
            out.append((xx, yy, wch, hch, c))
            xx += wch
            ww -= wch
        yy += hch
        hh -= hch
    return out


def rects_tiles_to_pixels(rects_tiles, tile: int, maxw: int, maxh: int):
    """
    Convierte rectángulos en tiles a rectángulos en pixeles y luego split.
    """
    rects = []
    for tx, ty, tw, th, c in rects_tiles:
        x = tx * tile
        y = ty * tile
        w = tw * tile
        h = th * tile
        rects.extend(split_rect_pixels(x, y, w, h, c, maxw, maxh))
    return rects


def emit_program(rects_pix, out_path: str, add_loop: bool = True):
    """
    Emite assembly:
      addi a0, zero, x  (solo si cambia)
      addi a1, zero, y
      addi a2, zero, w
      addi a3, zero, h
      addi a4, zero, c
      color a0,a1,a2,a3,a4
    """
    last = {"a0": None, "a1": None, "a2": None, "a3": None, "a4": None}

    def set_reg(f, reg: str, val: int):
        if last[reg] != val:
            f.write(f"addi {reg}, zero, {val}\n")
            last[reg] = val

    with open(out_path, "w", encoding="utf-8") as f:
        f.write("# Autogenerado por img2gpuisa_compact.py\n")
        f.write("# regs: a0=x, a1=y, a2=w, a3=h, a4=color\n\n")

        for (x, y, w, h, c) in rects_pix:
            set_reg(f, "a0", x)
            set_reg(f, "a1", y)
            set_reg(f, "a2", w)
            set_reg(f, "a3", h)
            set_reg(f, "a4", c)
            f.write("color a0, a1, a2, a3, a4\n\n")

        if add_loop:
            f.write("loop:\n")
            f.write("addi t0, t0, 0\n")
            f.write("j loop\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("image", help="input PNG/JPG/etc")
    ap.add_argument("-o", "--out", default="image.asm", help="output asm file")
    ap.add_argument("--colors", type=int, default=32, help="palette size for quantization (e.g. 16/32/64)")
    ap.add_argument("--tile", type=int, default=4, help="tile size (e.g. 2/4/5/8). Must divide 160 and 120.")
    ap.add_argument("--maxw", type=int, default=15, help="max raw_w (4 bits => 15)")
    ap.add_argument("--maxh", type=int, default=15, help="max raw_h (4 bits => 15)")
    ap.add_argument("--dither", action="store_true", help="use dithering during quantization")
    ap.add_argument("--no-loop", action="store_true", help="do not append infinite loop")
    args = ap.parse_args()

    if W % args.tile != 0 or H % args.tile != 0:
        raise SystemExit(f"tile must divide {W} and {H}. Try --tile 2,4,5,8")

    img = Image.open(args.image).convert("RGB").resize((W, H), resample=Image.BILINEAR)
    imgq = quantize_image(img, colors=args.colors, dither=args.dither)

    grid = build_tile_grid(imgq, tile=args.tile)
    rects_tiles = greedy_rectangles(grid)
    rects_pix = rects_tiles_to_pixels(rects_tiles, tile=args.tile, maxw=args.maxw, maxh=args.maxh)

    # stats
    num_color = len(rects_pix)
    print(f"Tiles grid: {W//args.tile}x{H//args.tile} = {(W//args.tile)*(H//args.tile)} cells")
    print(f"Rects (tiles): {len(rects_tiles)}")
    print(f"Rects (pixels after split w/h<= {args.maxw}/{args.maxh}): {num_color}")
    print(f"Writing: {args.out}")

    emit_program(rects_pix, args.out, add_loop=(not args.no_loop))


if __name__ == "__main__":
    main()

