#include <stdio.h>

int deviceStatus = 0;
static int privateEventTotal = 0;

static void updatePrivateEventTotal(void)
{
    privateEventTotal++;
}

void recordEvent(void)
{
    static int functionCallCount = 0;
    functionCallCount++;
    updatePrivateEventTotal();
    deviceStatus = 1;
    printf("Function calls: %d\n", functionCallCount);
}

void printMonitorSummary(void)
{
    printf("Private event total: %d\n", privateEventTotal);
}