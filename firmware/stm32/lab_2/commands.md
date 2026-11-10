# STM32 Lab 2 — Build, Execution, and Debugging Reference

## 1. Overview

This lab demonstrates how a bare-metal ARM Cortex-M4 program starts executing and how its runtime state can be inspected without `printf()`, UART, or STM32CubeIDE.

### Learning objectives

- Understand how the Cortex-M4 uses the vector table during reset.
- Identify the initial stack pointer and reset handler.
- Understand the execution path from `Reset_Handler()` to `main()`.
- Cross-compile C firmware using ARM GNU Toolchain.
- Inspect ELF symbols, sections, and machine instructions.
- Load and execute firmware using Renode.
- Read SRAM variables to verify program execution.

### Development environment

| Component              | Tool                |
| ---------------------- | ------------------- |
| Host operating system  | macOS               |
| Target processor       | ARM Cortex-M4       |
| Target microcontroller | STM32F407           |
| Compiler               | `arm-none-eabi-gcc` |
| Binary inspection      | ARM GNU Binutils    |
| Simulator              | Renode              |
| Container environment  | Docker Compose      |
| Firmware format        | ELF                 |

### Project structure

```text
embedded_lab/
├── docker-compose.yaml
├── firmware/
│   └── stm32/
│       └── lab_2/
│           ├── main.c
│           ├── startup.c
│           ├── linker.ld
│           ├── commands.md
│           └── build/
│               ├── firmware.elf
│               └── firmware.map
```

The `build/` directory contains generated files and is not part of the firmware source.

---

## 2. Compile the firmware

Run all commands in this section from the **repository root**.

### 2.1 Create the build directory

```bash
mkdir -p firmware/stm32/lab_2/build
```

### 2.2 Compile and link

```bash
arm-none-eabi-gcc \
  -mcpu=cortex-m4 \
  -mthumb \
  -std=c11 \
  -Wall -Wextra \
  -O0 -g3 \
  -ffreestanding \
  -fno-builtin \
  -nostdlib \
  -Wl,-T,firmware/stm32/lab_2/linker.ld \
  -Wl,-Map,firmware/stm32/lab_2/build/firmware.map \
  firmware/stm32/lab_2/startup.c \
  firmware/stm32/lab_2/main.c \
  -o firmware/stm32/lab_2/build/firmware.elf
```

### Important compiler options

| Option            | Purpose                                                       |
| ----------------- | ------------------------------------------------------------- |
| `-mcpu=cortex-m4` | Generate instructions for Cortex-M4                           |
| `-mthumb`         | Generate Thumb instructions                                   |
| `-std=c11`        | Use the C11 language standard                                 |
| `-Wall -Wextra`   | Enable useful compiler warnings                               |
| `-O0`             | Disable optimization for easier debugging                     |
| `-g3`             | Include detailed debugging information                        |
| `-ffreestanding`  | Compile for an environment without a hosted C runtime         |
| `-fno-builtin`    | Prevent assumptions about built-in library functions          |
| `-nostdlib`       | Do not automatically link standard libraries or startup files |
| `-Wl,-T,...`      | Pass the custom linker script to the linker                   |
| `-Wl,-Map,...`    | Generate a linker memory-map report                           |

**Expected result:**

```text
firmware/stm32/lab_2/build/firmware.elf
firmware/stm32/lab_2/build/firmware.map
```

The ELF contains the firmware's machine code, symbol information, and debugging metadata.

The map file explains how the linker placed sections and symbols in memory.

---

## 3. Inspect the firmware

These commands execute on macOS, not inside Renode.

### 3.1 Inspect ELF information

```bash
arm-none-eabi-readelf -h \
  firmware/stm32/lab_2/build/firmware.elf
```

Use this to inspect:

- Target architecture.
- ELF format.
- Entry-point address.
- Other ELF header metadata.

**Important:** The ELF entry point and the processor's hardware reset sequence are related but distinct. On reset, Cortex-M4 obtains its initial stack pointer and reset handler from the vector table.

### 3.2 Inspect the vector table

```bash
arm-none-eabi-objdump \
  -s -j .isr_vector \
  firmware/stm32/lab_2/build/firmware.elf
```

The vector table begins at:

```text
0x08000000
```

Its first two entries are:

| Address      | Meaning                          |
| ------------ | -------------------------------- |
| `0x08000000` | Initial Main Stack Pointer (MSP) |
| `0x08000004` | Reset handler address            |

For this project, the expected initial MSP is:

```text
0x20020000
```

This comes from the linker script:

```ld
_estack = ORIGIN(RAM) + LENGTH(RAM);
```

Calculation:

```text
RAM origin = 0x20000000
RAM size   = 0x00020000 (128 KiB)

Initial MSP = 0x20020000
```

The reset-handler vector contains the handler's address with the Thumb-state bit set.

For example, if the handler starts at:

```text
0x08000008
```

The vector entry should contain:

```text
0x08000009
```

ARM Cortex-M processors execute Thumb instructions.

**Note:** `objdump` displays raw bytes in memory order. On the little-endian Cortex-M4, the bytes for `0x20020000` appear as:

```text
00 00 02 20
```

### 3.3 Inspect symbols and addresses

```bash
arm-none-eabi-nm -n \
  firmware/stm32/lab_2/build/firmware.elf
```

Output recorded during this lab:

```text
08000000 R vector_table
08000008 T Reset_Handler
08000014 t calculate_result
0800002a T main
20000000 B boot_stage
20000004 B diagnostic_result
20020000 R _estack
```

#### Symbol types

| Symbol type | Meaning                                                                 |
| ----------- | ----------------------------------------------------------------------- |
| `T`         | Global symbol in the code section                                       |
| `t`         | Local symbol in the code section                                        |
| `R`         | Symbol classified as read-only data or an absolute linker-defined value |
| `B`         | Symbol in uninitialized or no-load storage                              |

The exact classification depends on the symbol and toolchain.

#### Important addresses

| Symbol              | Address      | Purpose                     |
| ------------------- | ------------ | --------------------------- |
| `vector_table`      | `0x08000000` | Reset information           |
| `Reset_Handler`     | `0x08000008` | Startup entry               |
| `calculate_result`  | `0x08000014` | Application function        |
| `main`              | `0x0800002A` | Application entry           |
| `boot_stage`        | `0x20000000` | Execution progress          |
| `diagnostic_result` | `0x20000004` | Calculation result          |
| `_estack`           | `0x20020000` | Initial stack pointer value |

These addresses were observed in this build. Re-run `nm` after modifying or rebuilding the firmware because symbol addresses can change.

### 3.4 Inspect memory sections

```bash
arm-none-eabi-readelf -S \
  firmware/stm32/lab_2/build/firmware.elf
```

Important sections:

| Section       | Location | Purpose                    |
| ------------- | -------- | -------------------------- |
| `.isr_vector` | Flash    | Vector table               |
| `.text`       | Flash    | Executable instructions    |
| `.rodata`     | Flash    | Read-only constants        |
| `.result`     | SRAM     | Diagnostic variables       |
| `.bss`        | SRAM     | Zero-initialized variables |

In this project's linker script, `.rodata` input sections are included within the output `.text` section.

The `.result` section uses `NOLOAD`, meaning storage is reserved in SRAM without corresponding initialized bytes in the load image.

### 3.5 Inspect program headers

```bash
arm-none-eabi-readelf -l \
  firmware/stm32/lab_2/build/firmware.elf
```

Use this to understand which memory regions are represented by loadable ELF segments.

**Sections describe the organization of the program. Segments describe how portions of the ELF are loaded into memory.**

### 3.6 Inspect ARM instructions

```bash
arm-none-eabi-objdump \
  -d \
  firmware/stm32/lab_2/build/firmware.elf
```

Look for:

```text
Reset_Handler
calculate_result
main
```

This shows the machine instructions generated from the C source.

To include C source alongside disassembly when debugging information is available:

```bash
arm-none-eabi-objdump \
  -d -S \
  firmware/stm32/lab_2/build/firmware.elf
```

### 3.7 Inspect firmware size

```bash
arm-none-eabi-size \
  firmware/stm32/lab_2/build/firmware.elf
```

This summarizes the firmware's section sizes.

For detailed memory allocation, inspect:

```text
firmware/stm32/lab_2/build/firmware.map
```

---

## 4. Start Renode

Run these commands from the repository root.

### 4.1 Start Docker Compose

```bash
docker compose up -d
```

Check the container status:

```bash
docker compose ps
```

### 4.2 Connect to the Renode Monitor

```bash
nc 127.0.0.1 1234
```

The following commands are entered into the **Renode Monitor**, not the macOS terminal.

### 4.3 Load the STM32F4 Discovery platform

```text
include @scripts/single-node/stm32f4_discovery.resc
```

This configures the simulated microcontroller and associated peripherals.

If the script automatically starts the simulation, pause it before loading a different firmware image.

For a clean experiment, use a fresh simulation session.

### 4.4 Load the firmware

```text
pause
sysbus LoadELF @/workspace/firmware/stm32/lab_2/build/firmware.elf
```

The `/workspace/firmware` path is the firmware directory mounted inside the Renode Docker container.

It is not a macOS filesystem path.

**Important:** Loading an ELF and starting CPU execution are separate operations.

---

## 5. Inspect the vector table in Renode

Before running the firmware, read the first two words of Flash.

### Initial stack pointer

```text
sysbus ReadDoubleWord 0x08000000
```

Expected:

```text
0x20020000
```

### Reset handler address

```text
sysbus ReadDoubleWord 0x08000004
```

For the documented build, expected:

```text
0x08000009
```

The actual reset handler starts at `0x08000008`; bit 0 of the vector entry indicates Thumb state.

### What this proves

The processor's reset information exists in the firmware image at the expected Flash addresses.

The vector table is data read by the CPU during reset, not a sequence of instructions executed from its first byte.

---

## 6. Execute the firmware

In the Renode Monitor:

```text
sysbus.cpu Reset
start
```

The expected execution sequence is:

```text
Reset
  |
  v
Read vector table
  |
  +--> MSP = 0x20020000
  |
  +--> Reset_Handler
           |
           v
         main()
           |
           v
      boot_stage = 1
           |
           v
      calculate_result(100)
           |
           v
      diagnostic_result = 125
           |
           v
      boot_stage = 2
           |
           v
      Infinite loop
```

The infinite loop keeps the firmware executing rather than returning from `main()`.

---

## 7. Inspect runtime variables

Pause the simulation:

```text
pause
```

The addresses recorded for this build are:

```text
boot_stage        = 0x20000000
diagnostic_result = 0x20000004
```

Read the first variable:

```text
sysbus ReadDoubleWord 0x20000000
```

Expected value:

```text
2
```

Read the second variable:

```text
sysbus ReadDoubleWord 0x20000004
```

Expected value:

```text
125
```

Renode may display these values in hexadecimal:

```text
2   = 0x00000002
125 = 0x0000007D
```

### Why this works

The firmware writes values directly into SRAM.

Renode can inspect the simulated memory independently of the firmware's input/output facilities.

Therefore, no `printf()`, UART, ITM, or LCD is required.

This technique is useful for debugging small bare-metal programs before implementing a logging interface.

---

## 8. Understand the diagnostic variables

The application declares:

```c
__attribute__((used, section(".result")))
volatile uint32_t boot_stage;

__attribute__((used, section(".result")))
volatile uint32_t diagnostic_result;
```

### `volatile`

Instructs the compiler that accesses to these objects have observable side effects.

This is important because their values are intended to be inspected externally.

It does not guarantee atomicity, synchronization, or initialization.

### `section(".result")`

Places the variables in a named input section.

The linker script maps that section into SRAM.

### `used`

Tells the compiler to emit the objects even if ordinary source-level reference analysis would otherwise permit removing them.

### `NOLOAD`

The linker script declares:

```ld
.result (NOLOAD) :
{
    KEEP(*(.result))
} > RAM
```

This reserves RAM for the variables without providing initialized data in the load image.

Their contents should not be assumed to be zero immediately after reset.

In this lab, both variables are explicitly assigned values before their final values are inspected.

---

## 9. Modification experiments

### Experiment A — Change the calculation

Change:

```c
diagnostic_result = calculate_result(100U);
```

To:

```c
diagnostic_result = calculate_result(200U);
```

Expected result:

```text
boot_stage        = 2
diagnostic_result = 225
```

Recompile, load the updated ELF in a fresh simulation, and inspect SRAM.

### Experiment B — Change execution progress

Comment out:

```c
boot_stage = 2U;
```

Expected:

```text
boot_stage        = 1
diagnostic_result = 125
```

This demonstrates how a variable can identify the last completed execution stage.

### Experiment C — Inspect generated instructions

Run:

```bash
arm-none-eabi-objdump \
  -d -S \
  firmware/stm32/lab_2/build/firmware.elf
```

Find `main()` and identify the instructions responsible for writing the diagnostic values.

Compare the assembly before and after modifying the source.

---

## 10. Common problems

### Firmware does not compile

Check:

- ARM GNU Toolchain is installed.
- The current working directory is the repository root.
- `build/` exists.
- Source and linker-script paths are correct.

Verify the compiler:

```bash
arm-none-eabi-gcc --version
```

### Renode cannot find the ELF

Check:

- Docker Compose is running.
- The firmware directory is mounted into the container.
- The ELF exists at the expected path.
- The Renode path uses `/workspace/firmware/...`, not the macOS path.

### Diagnostic values are incorrect

Check:

1. Was the firmware rebuilt after the latest changes?
2. Was the updated ELF loaded?
3. Did the CPU execute after reset?
4. Was the simulation paused before inspection?
5. Are the variable addresses still correct according to `nm`?

### Firmware does not reach `main()`

Inspect:

```bash
arm-none-eabi-objdump \
  -s -j .isr_vector \
  firmware/stm32/lab_2/build/firmware.elf
```

And:

```bash
arm-none-eabi-nm -n \
  firmware/stm32/lab_2/build/firmware.elf
```

Verify that:

- The initial MSP points into valid SRAM.
- The reset handler points into executable Flash.
- The reset-handler vector has its Thumb-state bit set.
- The startup code calls `main()`.

---

## 11. Current implementation limitations

This lab intentionally uses a minimal bare-metal runtime.

### Missing `.data` initialization

A normal C startup routine copies initialized global/static data from Flash into SRAM before calling `main()`.

The current startup code does not perform this operation.

### Missing `.bss` initialization

A normal C startup routine clears the `.bss` region before `main()`.

The current startup code does not perform this operation.

### Minimal vector table

The vector table contains only:

1. Initial MSP.
2. Reset handler.

It does not provide the full exception and interrupt vectors required by a general STM32 application.

### No standard output

The firmware does not implement:

- ITM/SWO logging.
- Semihosting.
- UART logging.
- Standard C library `printf()` support.

Memory-based diagnostics are used instead.

These limitations are intentional for the current lab and should be addressed in subsequent lessons where relevant.

---

## 12. Quick command reference

### macOS terminal — build

```bash
mkdir -p firmware/stm32/lab_2/build

arm-none-eabi-gcc \
  -mcpu=cortex-m4 -mthumb \
  -std=c11 -Wall -Wextra \
  -O0 -g3 \
  -ffreestanding -fno-builtin -nostdlib \
  -Wl,-T,firmware/stm32/lab_2/linker.ld \
  -Wl,-Map,firmware/stm32/lab_2/build/firmware.map \
  firmware/stm32/lab_2/startup.c \
  firmware/stm32/lab_2/main.c \
  -o firmware/stm32/lab_2/build/firmware.elf
```

### macOS terminal — inspect

```bash
# Vector table
arm-none-eabi-objdump -s -j .isr_vector \
  firmware/stm32/lab_2/build/firmware.elf

# Symbols and addresses
arm-none-eabi-nm -n \
  firmware/stm32/lab_2/build/firmware.elf

# Disassembly with C source
arm-none-eabi-objdump -d -S \
  firmware/stm32/lab_2/build/firmware.elf

# ELF sections
arm-none-eabi-readelf -S \
  firmware/stm32/lab_2/build/firmware.elf

# ELF program headers
arm-none-eabi-readelf -l \
  firmware/stm32/lab_2/build/firmware.elf

# Firmware size
arm-none-eabi-size \
  firmware/stm32/lab_2/build/firmware.elf
```

### macOS terminal — start Renode

```bash
docker compose up -d
nc 127.0.0.1 1234
```

### Renode Monitor — load and execute

```text
include @scripts/single-node/stm32f4_discovery.resc

pause

sysbus LoadELF @/workspace/firmware/stm32/lab_2/build/firmware.elf

sysbus ReadDoubleWord 0x08000000
sysbus ReadDoubleWord 0x08000004

sysbus.cpu Reset
start

pause

sysbus ReadDoubleWord 0x20000000
sysbus ReadDoubleWord 0x20000004
```

The two SRAM addresses are specific to the documented build. Recheck them using `arm-none-eabi-nm` whenever the firmware changes.

---

## 13. Key takeaways

1. **Reset does not call `main()` directly.** The processor reads its initial execution state from the vector table.

2. **The linker controls memory placement.** The linker script determines where code and data reside in Flash and SRAM.

3. **Startup code establishes the C runtime environment.** The current implementation is minimal and does not yet initialize `.data` or `.bss`.

4. **ELF symbols connect source code to memory addresses.** Tools such as `nm`, `readelf`, and `objdump` reveal how the compiled firmware is organized.

5. **A console is not required to observe firmware execution.** Debuggers and simulators can inspect memory directly.

6. **Rebuilding can change addresses.** Always use the current ELF as the authoritative source for symbol locations.
