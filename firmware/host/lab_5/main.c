#include <stdio.h>
#include <limits.h>
void task1(void)
{
    printf("Bits per byte: %d\n", CHAR_BIT);
    printf("Char %zu bytes range %d to %d\n",
           sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned char maximum: %d\n", UCHAR_MAX);
    printf("short %zu bytes range %d to %d\n",
           sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short maximum: %u\n", USHRT_MAX);
    printf("int: %zu bytes, range %d to %d\n",
           sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int maximum: %u\n", UINT_MAX);
    printf("long: %zu bytes, range %ld to %ld\n",
           sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long maximum: %lu\n", ULONG_MAX);
    printf("long long: %zu bytes, range %lld to %lld\n",
           sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("unsigned long long maximum: %llu\n", ULLONG_MAX);
}
void task2(void)
{
    unsigned char distanceAtoB = 160;
    unsigned char distanceBtoC = 255;
    unsigned short totalDistance = distanceAtoB + distanceBtoC;
    unsigned char narrowedDistance = distanceAtoB + distanceBtoC;
    printf("A to B: %u km\n", (unsigned int)distanceAtoB);
    printf("B to C: %u km\n", (unsigned int)distanceBtoC);
    printf("Total distance: %u km\n",
           (unsigned int)totalDistance);
    printf("Narrowed result: %u km\n",
           (unsigned int)narrowedDistance);
    printf("Hexadecimal: 0x%X\n",
           (unsigned int)totalDistance);
    printf("Octal: %o\n", (unsigned int)totalDistance);
}
void task3(void)
{
    char deviceGrade = 'A';
    char deviceName[] = "STM32";
    char city[] = "Cairo";

    printf("Device: %s\n", deviceName);
    printf("City: %s\n", city);

    printf("Grade: %c\n", deviceGrade);
    printf("Grade ASCII: %d\n", (int)deviceGrade);
    printf("Grade hex: 0x%X\n",
           (unsigned int)deviceGrade);

    printf("Grade size: %zu byte\n", sizeof(deviceGrade));
    printf("Device name size: %zu bytes\n", sizeof(deviceName));
    printf("City size: %zu bytes\n", sizeof(city));
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
    return 0;
}