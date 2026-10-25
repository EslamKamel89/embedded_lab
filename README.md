# Embedded C Lab

A growing collection of practical experiments exploring C programming, microcontrollers, and bare-metal embedded systems development.

The repository is organized into independent labs that demonstrate concepts through runnable code, compilation, simulation, and debugging.

## Repository Organization

Experiments are organized by execution environment:

- **`firmware/host/`** — C programs compiled and executed on the development computer.
- **`firmware/stm32/`** — Bare-metal firmware targeting STM32 microcontrollers.
- **`renode/`** — Simulation scripts and configurations, as needed.
- **`docker-compose.yaml`** — Docker configuration for the Renode simulation environment.
- **`commands.txt`** — Useful build, execution, and debugging commands.

Each environment can contain multiple numbered labs. Additional directories, experiments, and supporting tools will be introduced as the repository evolves.

## Development Environment

The project uses the following tools, depending on the experiment:

| Tool              | Purpose                                         |
| ----------------- | ----------------------------------------------- |
| Clang             | Compile and run native C programs               |
| Arm GNU Toolchain | Cross-compile firmware for ARM Cortex-M         |
| Renode            | Simulate microcontrollers and inspect execution |
| Docker            | Run the simulation environment                  |

Some experiments run directly on the host computer, while others target simulated or physical microcontrollers.

### VS Code

Open this repository folder in VS Code and enable the recommended **C/C++** extension
(`ms-vscode.cpptools`). Run **Developer: Reload Window** after changing the setup.
The workspace enables IntelliSense and error squiggles, overriding the disabled
IntelliSense engine in the current user's settings. It disables STM32Cube clangd
for this workspace to avoid competing C language services.

Use **C/C++: Select a Configuration** in the Command Palette:

- **Mac** for `firmware/host/` (Apple Clang, C11, Apple Silicon).
- **STM32 Cortex-M4** for `firmware/stm32/` (Homebrew Arm GCC and the flags used in `commands.txt`).

Switch configurations when moving between host and STM32 files. The compiler paths
in `.vscode/c_cpp_properties.json` and `.vscode/tasks.json` match this Mac; adjust
them on another machine. System header paths are discovered from each compiler.

Completion opens as you type, or with **Control+Space**. Use **Command+.** for
available quick fixes and **Command+Shift+M** to view Problems. Headers may still
need to be included manually; automatic header insertion is not guaranteed for
every C symbol. For example, `printf` needs `<stdio.h>` and `CHAR_BIT` needs
`<limits.h>`, but `sizeof` is a built-in operator and needs no header.

For compiler diagnostics, save the active `.c` file and press **Command+Shift+B**
to check a host file. For STM32, run **Tasks: Run Task → C: Check active STM32 file**.
These tasks check syntax and warnings without producing an executable or checking
linker errors. Live IntelliSense diagnostics appear while editing.

If live diagnostics remain missing, confirm the file language is **C** in the
status bar, the workspace is trusted, and the C/C++ extension is enabled for the
current VS Code profile. Run **C/C++: Log Diagnostics** to inspect the selected
compiler and header paths.

## Building and Running

Build and execution instructions depend on the lab.

For a native C program:

```bash
clang -std=c11 -Wall -Wextra -g main.c -o hello
./hello
```

For bare-metal firmware, the workflow typically involves:

1. Cross-compiling the C source and startup code.
2. Linking the firmware using a target-specific linker script.
3. Producing an ELF executable.
4. Loading the ELF into Renode or onto a physical microcontroller.
5. Inspecting execution, processor state, or memory.

Refer to the relevant lab files and `commands.txt` for specific commands.

## Topics

The repository progressively explores:

- C language fundamentals and memory behavior.
- Integer types, pointers, and bitwise operations.
- Native and cross-compilation.
- Microcontroller architecture and memory maps.
- Bare-metal startup and linker scripts.
- Compiler optimization and generated assembly.
- Memory-mapped peripheral access.
- Embedded debugging and simulation.

Additional topics and experiments will be added as development progresses.

## Purpose

The goal is to build a practical understanding of embedded software by connecting C source code to its actual execution on a processor.

Each experiment emphasizes observable behavior, memory state, and the relationship between source code, compiler output, and hardware or simulated hardware.
