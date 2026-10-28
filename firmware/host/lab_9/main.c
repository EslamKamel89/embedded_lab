#include <stdio.h>

void task1(void)
{
    printf("=== Task 1: Addresses ===\n");
    char letter = 'A';
    short sensorValue = -25;
    int counter = 100;
    printf("letter value: %c\n", letter);
    printf("letter address: %p\n", (void *)&letter);

    printf("sensor value: %d\n", sensorValue);
    printf("sensor address: %p\n", (void *)&sensorValue);

    printf("counter value: %d\n", counter);
    printf("counter address: %p\n", (void *)&counter);
}
void task2(void)
{
    printf("=== Task 2: Memory Layout ===\n");
    char first = 'A';
    char second = 'B';
    char third = 'C';
    printf("first:  %p\n", (void *)&first);
    printf("second: %p\n", (void *)&second);
    printf("third:  %p\n", (void *)&third);

    printf("char size: %zu byte\n", sizeof(char));
}
void task3(void)
{
    printf("=== Task 3: Pointer Variable ===\n");
    int reading = 500;
    int *readingAddress = &reading;
    printf("reading: %d\n", reading);
    printf("&reading: %p\n", (void *)&reading);
    printf("readingAddress: %p\n", (void *)readingAddress);
    printf("*readingAddress: %d\n", *readingAddress);
    *readingAddress = 900;
    printf("Updated reading: %d\n", reading);
}
void task4(void)
{
    printf("=== Task 4: Address as Integer ===\n");
    char letter = 'A';
    uintptr_t numericAddress = (uintptr_t)&letter;
    printf("Pointer address: %p\n", (void *)&letter);

    printf("Pointer size: %zu bytes\n", sizeof(&letter));
    printf("Integer size: %zu bytes\n",
           sizeof(numericAddress));
}
int main(void)
{
    printf("---------------------------\n");
    task1();
    printf("---------------------------\n");
    task2();
    printf("---------------------------\n");
    task3();
    printf("---------------------------\n");
    task4();
    printf("---------------------------\n");
    return 0;
}