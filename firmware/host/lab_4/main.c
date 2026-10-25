#include <limits.h>
#include <stdio.h>

void task1(void)
{
  printf("Bits per byte: %d\n", CHAR_BIT);
  printf("char:      %zu bytes\n", sizeof(char));
  printf("short:     %zu bytes\n", sizeof(short));
  printf("unsigned short: %zu bytes\n", sizeof(unsigned short));
  printf("int:       %zu bytes\n", sizeof(int));
  printf("unsigned int:   %zu bytes\n", sizeof(unsigned int));
  printf("long:      %zu bytes\n", sizeof(long));
  printf("long long: %zu bytes\n", sizeof(long long));
  printf("signed char range: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
  printf("unsigned char maximum: %u\n", UCHAR_MAX);
  printf("short range: %d to %d\n", SHRT_MIN, SHRT_MAX);
  printf("unsigned short maximum: %u\n", USHRT_MAX);
  printf("int range: %d to %d\n", INT_MIN, INT_MAX);
  printf("unsigned int maximum: %u\n", UINT_MAX);
  printf("long range: %ld to %ld\n", LONG_MIN, LONG_MAX);
  printf("unsigned long maximum: %lu\n", ULONG_MAX);
  printf("long long range: %lld to %lld\n", LLONG_MIN, LLONG_MAX);
  printf("unsigned long long maximum: %llu\n", ULLONG_MAX);
}
void task2(void)
{
  unsigned char distanceAtoB = 160;
  unsigned char distanceBtoC = 255;
  unsigned short distanceAtoC = distanceAtoB + distanceBtoC;
  unsigned char distanceAtoC_check = distanceAtoB + distanceBtoC;
  printf("A to B: %u km\n", (unsigned int)distanceAtoB);
  printf("B to C: %u km\n", (unsigned int)distanceBtoC);
  printf("Total distance: %u km\n", (unsigned int)distanceAtoC);
  printf("Total distance check: %u km\n", (unsigned int)distanceAtoC_check);
}
void task3(void)
{
  char grade = 'A';
  char name[] = "Eslam";
  printf("Name: %s\n", name);
  printf("Grade: %c\n", grade);
  printf("Grade ASCII value: %d\n", (int)grade);
  printf("Size of letter: %zu\n", sizeof(grade));
  printf("Size of name: %zu\n", sizeof(name));
}
void task4(void)
{
  char letter = 'A';
  printf("Letter: %c\n", letter);
  printf("Letter ASCII value: %d\n", (int)letter);
  printf("Size of letter: %zu\n", sizeof(letter));
  printf("Letter hexadecimal value: %x\n", (unsigned int)letter);
}
void task5(void)
{
  int temperature = -25;
  unsigned int distance = 200;
  char grade = 'A';
  char city[] = "Cairo";

  printf("Temperature: %d C\n", temperature);
  printf("Distance: %u km\n", distance);
  printf("Distance in hex: 0x%X\n", distance);
  printf("Grade: %c\n", grade);
  printf("City: %s\n", city);
  printf("%d %c %s\n", temperature, grade, city);
}

void task6(void)
{
  signed char signedValue = -25;
  unsigned char rawBits = (unsigned char)signedValue;
  printf("Signed value: %d\n", (int)signedValue);
  printf("Unsigned interpretation: %u\n", (unsigned int)rawBits);
}
void task7(void)
{
  unsigned char unsignedValue = UCHAR_MAX;
  signed char signedValue = SCHAR_MAX;
  printf("Unsigned maximum: %u\n",
         (unsigned int)unsignedValue);
  printf("Signed maximum: %d\n",
         (int)signedValue);
  unsignedValue++;
  printf("Unsigned after increment: %u\n",
         (unsigned int)unsignedValue);
  signedValue++;
  printf("Signed after increment: %d\n",
         (int)signedValue);
}
int main(void)
{
  // task1();
  // task2();
  // task3();
  // task4();
  // task5();
  // task6();
  task7();
  return 0;
}
