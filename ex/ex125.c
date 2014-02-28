#include <stdio.h>

int main(void) {

  char test = 0x41;
  char test2 = 0xFF;

  if(test == 0x41)
    printf("check 1 passed\n");
  else
    printf("check 1 failed\n");

  if(test2 == 0xFF)
    printf("check 2 passed\n");
  else
    printf("check 2 failed\n");

  if((unsigned char)test2 == 0xFF)
    printf("check 3 passed\n");
  else
    printf("check 3 failed\n");
  return 0;
}
