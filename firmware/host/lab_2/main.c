#include <stdio.h>
#include <unistd.h>
int main(void) {
  printf("Hello, World!\n");
  //   printf("Goodbye\0World!\n");
  for (int i = 0; i <= 100; i++) {
    printf("Loading: %d%%\r", i);
    fflush(stdout);
    sleep(1);
  }
  printf("\nDone\n");
  return 0;
}