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
