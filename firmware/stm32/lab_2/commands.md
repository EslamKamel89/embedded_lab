Compile the firmware

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
  -Wl,-T,linker.ld \
  -Wl,-Map,build/firmware.map \
  startup.c \
  main.c \
  -o build/firmware.elf

```

Inspect the vector table

```bash
arm-none-eabi-objdump \
  -s -j .isr_vector \
  build/firmware.elf

```

inspect their symbols

```bash
arm-none-eabi-nm -n \
  build/firmware.elf
```

Load firmware in Renode

Start the existing Docker service if it is not running

```bash
docker compose up -d
```

Connect to the monitor

```bash
nc 127.0.0.1 1234
```

In the Renode monitor, load your existing STM32F4 Discovery platform

```bash
include @scripts/single-node/stm32f4_discovery.resc
```

Then load the new ELF using the machine's system bus

```bash
sysbus LoadELF @/workspace/firmware/stm32/lab_2/build/firmware.elf

```

Before starting execution, inspect the vector table bytes

```bash
sysbus ReadDoubleWord 0x08000000
sysbus ReadDoubleWord 0x08000004
```

reset and execute

```bash
sysbus.cpu Reset
start

```

Find diagnostic variable addresses using nm

```bash

arm-none-eabi-nm -n firmware/stm32/lab_2/build/firmware.elf
```

this is the output in the console for the previous command

```txt
08000000 R vector_table
08000008 T Reset_Handler
08000014 t calculate_result
0800002a T main
20000000 B boot_stage
20000004 B diagnostic_result
20020000 R _estack
```

pause the simulation in the renode monitor

```bash
pause
```

Then read the variables

```
sysbus ReadDoubleWord 0x20000000
sysbus ReadDoubleWord 0x20000004
```
