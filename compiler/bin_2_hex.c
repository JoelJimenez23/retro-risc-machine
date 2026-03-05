#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *f = fopen("bin_file.txt", "r");
    if (!f) {
        perror("No se pudo abrir input.txt");
        return 1;
    }

    int c;
    int bits_in_nibble = 0;   // cuántos bits llevamos (0..4)
    unsigned int nibble = 0;  // acumulador de 4 bits
    int hex_count = 0;        // cuántos hex hemos impreso en la línea (0..8)

    while ((c = fgetc(f)) != EOF) {
        if (c == '0' || c == '1') {
            nibble = (nibble << 1) | (unsigned int)(c - '0');
            bits_in_nibble++;

            if (bits_in_nibble == 4) {
                // convertir nibble (0..15) a hex
                char hex_digit = (nibble < 10) ? (char)('0' + nibble)
                                               : (char)('A' + (nibble - 10));

                putchar(hex_digit);
                hex_count++;

                if (hex_count == 8) {
                    putchar('\n');
                    hex_count = 0;
                }

                // reset para el siguiente nibble
                nibble = 0;
                bits_in_nibble = 0;
            }
        } else if (isspace((unsigned char)c)) {
            // ignorar espacios, tabs, saltos de línea
            continue;
        } else {
            // si hay caracteres raros, avisa y sal
            fprintf(stderr, "Error: caracter no valido en el archivo: '%c'\n", c);
            fclose(f);
            return 1;
        }
    }

    fclose(f);

    // Si quedaron bits sueltos al final (no múltiplo de 4), avisa.
    if (bits_in_nibble != 0) {
        fprintf(stderr,
                "\nAviso: el archivo termina con %d bit(s) suelto(s). "
                "Se ignoraron (falta completar un nibble de 4 bits).\n",
                bits_in_nibble);
    }

    // Si la última línea no terminó justo en múltiplo de 8, agrega salto final.
    if (hex_count != 0) {
        putchar('\n');
    }

    return 0;
}

