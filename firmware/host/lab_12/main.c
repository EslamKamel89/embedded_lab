#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
int main(void)
{
    int sensorReading = 750;
    int *readingAddress = &sensorReading;
    uintptr_t numericAddress = (uintptr_t)readingAddress;
    printf("Original reading: %d\n", sensorReading);
    printf("Pointer address: %p\n", (void *)readingAddress);
    printf("Numeric address: 0x%" PRIxPTR "\n", numericAddress);
    {
        int sensorReading = 900;
        printf("Local reading: %d\n", sensorReading);
    }
    printf("Original after block: %d\n", sensorReading);
    return 0;
}