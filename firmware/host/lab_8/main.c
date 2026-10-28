#include <stdio.h>

int sharedCounter;
int sensorValue = 10;
void task1(void);
void task2(void);
void task3(void);
void task4(void);
void updateCounter(void);
void task1(void)
{
    printf("=== Task 1 ===\n");
    int examScore;
    examScore = 540;
    int sensorReading = 25;
    printf("Exam score: %d\n", examScore);
    printf("Sensor reading: %d\n", sensorReading);
}
void updateCounter(void)
{
    sharedCounter = 800;
}
void task2(void)
{
    printf("=== Task 2 ===\n");
    sharedCounter = 900;
    printf("Before update: %d\n", sharedCounter);
    updateCounter();
    printf("After update: %d\n", sharedCounter);
}
void task3(void)
{
    printf("=== Task 3 ===\n");
    printf("Global sensor: %d\n", sensorValue);

    int sensorValue = 20;
    printf("Function local: %d\n", sensorValue);
    {
        int sensorValue = 30;
        printf("Inner block: %d\n", sensorValue);

        sensorValue = 40;
        printf("Inner modified: %d\n", sensorValue);
    }
    printf("After block: %d\n", sensorValue);
}
void task4(void)
{
    printf("=== Task 4 ===\n");
    printf("Global initial value: %d\n", sharedCounter);

    int localValue = 0;
    localValue = localValue + 10;

    printf("Initialized local: %d\n", localValue);
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
    sharedCounter = 0;
    task4();
    printf("---------------------------\n");
    extern int deviceStatus;
    printf("Device status: %d\n", deviceStatus);
}