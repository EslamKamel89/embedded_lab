#include <stdio.h>
#include "math.h"

int main(void)
{
    printf("Add: %d\n", math_add(12, 13));
    printf("Sub: %d\n", math_sub(20, 8));
    printf("Mul: %lld\n", math_mul(100000, 100000));
    printf("Div: %.4f\n", (double)math_div(80, 3));
    return 0;
}