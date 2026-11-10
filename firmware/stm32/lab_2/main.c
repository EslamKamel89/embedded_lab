#include <stdint.h>

__attribute__((used, section(".result"))) volatile uint32_t boot_stage;

__attribute__((used, section(".result"))) volatile uint32_t diagnostic_result;

static uint32_t calculate_result(uint32_t input)
{
    return input + 25U;
}

int main(void)
{
    boot_stage = 1U;
    diagnostic_result = calculate_result(100U);
    boot_stage = 2U;
    while (1)
    {
    }
}
