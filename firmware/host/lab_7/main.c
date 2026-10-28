#include <stdio.h>
#include <limits.h>
#include <stddef.h>

void printIntegerSizes(void)
{
    printf("=== Integer Sizes ===\n");
    printf("char      : %zu bytes\n", sizeof(char));
    printf("short     : %zu bytes\n", sizeof(short));
    printf("int       : %zu bytes\n", sizeof(int));
    printf("long      : %zu bytes\n", sizeof(long));
    printf("long long : %zu bytes\n", sizeof(long long));
}

void printShortLimits(void)
{
    printf("=== Short Limits ===\n");
    printf("Signed min : %d\n", SHRT_MIN);
    printf("Signed max : %d\n", SHRT_MAX);
    printf("Unsigned max : %u\n", (unsigned int)USHRT_MAX);
    printf("Unsigned hex : 0x%04X\n", (unsigned int)USHRT_MAX);
    unsigned int totalValues = (unsigned int)USHRT_MAX + 1U;
    printf("Total unsigned values : %u\n", totalValues);
}
void printSignedRepresentation()
{
    printf("=== Signed Representation ===\n");
    short temperature = -25;
    unsigned short rawTemperature = (unsigned short)temperature;
    printf("Signed   : %d\n", (int)temperature);
    printf("Unsigned : %u\n", (unsigned int)rawTemperature);
    printf("Hex      : 0x%04X\n", (unsigned int)rawTemperature);
    short errorCode = -1;
    unsigned short rawErrorCode = (unsigned short)errorCode;
    printf("Error signed : %d\n", (int)errorCode);
    printf("Error hex    : 0x%04X\n", (unsigned int)rawErrorCode);
}
void printSensorStorageReport()
{
    printf("=== Sensor Storage Report ===\n");
    short temperature = -25;
    int sampleCount = 1000;
    long long accumulatedSamples = 9000000;

    size_t temperatureBytes = sizeof(temperature);
    size_t sampleBytes = sizeof(sampleCount);
    size_t accumulatedBytes = sizeof(accumulatedSamples);
    size_t totalBytes =
        temperatureBytes + sampleBytes + accumulatedBytes;
    printf("Temperature: %d\n", (int)temperature);
    printf("Raw temperature: 0x%04X\n",
           (unsigned int)(unsigned short)temperature);
    printf("Temperature storage: %zu bytes, %zu bits\n",
           temperatureBytes, temperatureBytes * CHAR_BIT);
    printf("Sample count storage: %zu bytes, %zu bits\n",
           sampleBytes, sampleBytes * CHAR_BIT);
    printf("Accumulated storage: %zu bytes, %zu bits\n",
           accumulatedBytes, accumulatedBytes * CHAR_BIT);
    printf("Total object sizes: %zu bytes\n", totalBytes);
}
int main(void)
{
    printf("-------------------------------------\n");
    printf("task 1\n");
    printIntegerSizes();
    printf("-------------------------------------\n");
    printf("task 2\n");
    printShortLimits();
    printf("-------------------------------------\n");
    printf("task 3\n");
    printSignedRepresentation();
    printf("-------------------------------------\n");
    printf("task 4\n");
    printSensorStorageReport();
    printf("-------------------------------------\n");

    return 0;
}