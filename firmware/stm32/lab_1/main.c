#include <stdint.h>

// Place this variable at a predictable SRAM address.
__attribute__((used, section(".result")))

volatile uint32_t counter;

int main(void) {
  counter = 5;
  counter++;
  while (1) {
    // Keep the firmware running.
  }
}