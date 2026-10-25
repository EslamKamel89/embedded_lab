#include <stdio.h>
#include <unistd.h>
int main(void) {
  for (int progress = 0; progress <= 5; progress++) {
    printf("Progress: %d%%\r", progress * 20);
    fflush(stdout);
    sleep(1);
  }
  printf("\nDone\n");
  return 0;
}