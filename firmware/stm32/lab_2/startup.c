#include <stdint.h>

extern int main(void);
extern uint32_t _estack;

void Reset_Handler(void)
{
    main();
    while (1)
    {
    }
}

__attribute__((used, section(".isr_vector")))
const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,
    (uintptr_t)&Reset_Handler,
};
