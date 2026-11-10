#include <stdio.h>

#include "measurements.h"

int main(void)
{
    int first = 0x87;
    int second = 0x187;
    int third = 0x289;

    printf("0x%X -> 0x%X\n", first, convert_to_byte(first));
    printf("0x%X -> 0x%X\n", second, convert_to_byte(second));
    printf("0x%X -> 0x%X\n", third, convert_to_byte(third));

    return 0;
}