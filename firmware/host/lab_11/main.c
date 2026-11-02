#include <stdio.h>

extern int deviceStatus;
// extern int privateEventTotal;

void updatePrivateTotal(void);

void recordEvent(void);

void printMonitorSummary(void);

void printAsciiExample(void)
{
    char first = 65;
    char second = 'p';
    char third = 'p';
    char fourth = 'l';
    char fifth = 'e';
    printf("Text: %c%c%c%c%c\n", first, second, third, fourth, fifth);
    printf("ASCII of A: %d\n", first);
    printf("ASCII of p: %d\n", second);
}

int main(void)
{
    printf("Initial status: %d\n", deviceStatus);
    // printf("Private event total: %d\n", privateEventTotal);
    // updatePrivateTotal();
    recordEvent();
    recordEvent();
    recordEvent();
    recordEvent();

    printMonitorSummary();

    printf("Final status: %d\n", deviceStatus);

    printAsciiExample();

    return 0;
}