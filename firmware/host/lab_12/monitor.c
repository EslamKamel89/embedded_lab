#include <stdio.h>

int deviceStatus = 0;
static int eventCount = 0;
static void incrementEventCount(void)
{
    eventCount++;
}
void recordEvent(void)
{
    incrementEventCount();
    deviceStatus = 1;
}
void printEventCount(void)
{
    printf("Event count: %d\n", eventCount);
}