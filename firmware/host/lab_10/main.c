#include <stdio.h>

extern int deviceStatus;
extern void updateDeviceStatus(void);

int main(void)
{
    printf("Initial status: %d\n", deviceStatus);
    updateDeviceStatus();
    printf("Updated status: %d\n", deviceStatus);
    return 0;
}