---

# 📄 README actualizado (propuesta)

Te dejo una versión lista para copiar/pegar:

---

# 🧠 Retro RISC Machine

A minimal **RISC-V inspired system** built from scratch, including:

* 🧩 A **single-cycle processor in Verilog**
* 🧮 A **custom compiler toolchain in C**
* 🖥️ A **VGA image rendering pipeline**
* 📂 Memory integration via `.dat` files

This project explores the full stack of computer architecture, from **high-level code to hardware execution**.

---

## 🚀 Overview

The goal of this project is to understand how software translates into hardware execution by implementing:

1. A **custom compiler**
2. A **binary → memory pipeline**
3. A **RISC-style processor**
4. A **basic graphics output (VGA)**

---

## 🧱 Project Structure

```
retro-risc-machine/
│
├── compiler/        # Custom compiler (C → binary → hex)
├── processor/       # Verilog CPU (single-cycle RISC-V style)
├── image_vga/       # VGA output + memory visualization
└── README.md
```

---

## ⚙️ Components

### 🧮 Compiler (`/compiler`)

Custom compiler written in C that:

* Tokenizes input source code
* Parses grammar rules
* Generates binary instructions
* Converts binary → hex for memory loading

#### Key files:

* `main.c` → compiler entry point
* `scanner.h`, `parser.h` → frontend
* `gencode.h` → code generation
* `bin_2_hex.c` → memory formatting

#### Output:

* `bin_file.txt`
* `memfile.dat` (used by processor)

---

### 🖥️ Processor (`/processor/single-cycle`)

A **single-cycle RISC-V-like CPU** implemented in Verilog.

#### Features:

* ALU
* Register file
* Instruction memory
* Data memory
* Control unit
* Datapath

#### Key modules:

* `alu.v`
* `controller.v`
* `datapath.v`
* `register_file.v`
* `imem.v`, `dmem.v`
* `top.v`

#### Simulation:

```bash
./run.sh
```

Produces:

* `probando.vcd` (waveform)

---

### 🎨 VGA Output (`/image_vga`)

Pipeline for displaying images using memory:

* Converts image → memory format
* Loads into simulated memory
* Displays via VGA logic

#### Files:

* `image.asm`
* `memfile.dat`
* `main.py` → preprocessing
* `run.sh`

---

## 🔄 Workflow

```
[ Source Code ]
        ↓
[ Compiler (C) ]
        ↓
[ Binary / Hex ]
        ↓
[ memfile.dat ]
        ↓
[ Verilog CPU ]
        ↓
[ Execution / VGA Output ]
```

---

## ▶️ How to Run

### 1. Compile program

```bash
cd compiler
gcc main.c -o compiler
./compiler test.txt
```

---

### 2. Load into processor

Move generated `.dat` file:

```bash
cp memfile.dat ../processor/single-cycle/
```

---

### 3. Run simulation

```bash
cd ../processor/single-cycle
./run.sh
```

---

### 4. View waveform

```bash
gtkwave probando.vcd
```

---

## 🧪 Current Status

✅ Working components:

* Compiler pipeline (basic programs)
* Instruction execution
* Memory loading
* Simulation environment

⚠️ Limitations:

* Single-cycle design (no pipeline)
* Limited instruction set
* No hazard handling
* Basic graphics pipeline

---

## 🧠 Learning Goals

This project explores:

* Computer architecture (datapath + control)
* Compiler design basics
* Hardware/software co-design
* Memory systems
* Low-level execution model

---

## 🔮 Future Work

Planned improvements:

* [ ] Pipeline implementation (5-stage)
* [ ] Hazard detection / forwarding
* [ ] Cache simulation
* [ ] Interrupt handling
* [ ] Expanded ISA
* [ ] GPU-style accelerator experiments (CNN inference?)

---

## 🎯 Why This Project Matters

This project is a step toward:

* OS development
* Kernel programming
* Hardware-aware software
* CPU/GPU architecture research

---

## 📚 References

* Harris & Harris — *Digital Design and Computer Architecture*
* Patterson & Hennessy — *Computer Organization and Design*
* RISC-V ISA Specification

---

## 👤 Author

Joel Jimenez
Computer Science @ UTEC
Interested in:

* Computer Architecture
* Operating Systems
* Hardware Acceleration (AI)

---

# 🧠 Feedback real (importante)

Tu proyecto **ya está en nivel serio**, no es básico. Pero para que sea fuerte de verdad (tipo maestría / paper), le faltan estas cosas clave:

### 🔥 Lo más importante que falta

* Pipeline (esto es *CRÍTICO*)
* ISA bien definida (aunque sea subset formal de RISC-V)
* Benchmarks (aunque sean simples)
* Documentar decisiones de diseño

---
