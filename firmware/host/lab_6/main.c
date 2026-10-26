#include <stdio.h>
#include <limits.h>

void task1(void)
{
    printf("=== Integer Type Sizes ===\n");
    printf("char      : %zu bytes\n", sizeof(char));
    printf("short     : %zu bytes\n", sizeof(short));
    printf("int       : %zu bytes\n", sizeof(int));
    printf("long      : %zu bytes\n", sizeof(long));
    printf("long long : %zu bytes\n", sizeof(long long));
}
void task2(void)
{
    printf("=== Short Integer Ranges ===\n");
    printf("Signed short : %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short : 0 to %u\n", (unsigned int)USHRT_MAX);
    printf("Bits per byte: %d\n", CHAR_BIT);
    printf("Bits in short: %zu\n", sizeof(short) * CHAR_BIT);
}
void task3(void)
{
    printf("=== Two's Complement ===\n");
    short signedValue = -25;
    unsigned short rawBits = (unsigned short)signedValue;
    printf("Signed Value: %d\n", signedValue);
    printf("Unsigned Value (raw bits): %u\n", (unsigned int)rawBits);
    printf("Hex value (raw bits): 0x%04X\n", (unsigned int)rawBits);
    short positiveValue = 25;
    printf("Positive 25 : 0x%04X\n", (unsigned int)(unsigned short)positiveValue);
}

void task4(void)
{
    printf("=== sizeof Variables ===\n");
    short sensorValue = -25;
    int counter = 1000;
    long long history = 900;
    size_t sensorBytes = sizeof(sensorValue);
    size_t counterBytes = sizeof(counter);
    size_t historyBytes = sizeof(history);

    printf("Size of sensorValue: %zu bytes\n", sensorBytes);
    printf("Size of counter: %zu bytes\n", counterBytes);
    printf("Size of history: %zu bytes\n", historyBytes);
    printf("Total : %zu bytes\n", sensorBytes + counterBytes + historyBytes);
}
int main(void)
{
    printf("----------------------------\n");
    printf("Task 1:\n");
    task1();
    printf("----------------------------\n");
    printf("Task 2:\n");
    task2();
    printf("----------------------------\n");
    printf("Task 3:\n");
    task3();
    printf("----------------------------\n");
    printf("Task 4:\n");
    task4();
    printf("----------------------------\n");
    return 0;
}