#include <stdio.h>

int main(void) {

  char test = 0x41;
  char test2 = 0xFF;
  char test3 = 0x100;

  if(test == 0x41)
    printf("check 1 passed\n");
  else
    printf("check 1 failed\n");

  if((unsigned char) test2 == 0xFF)
    printf("check 2 passed\n");
  else
    printf("check 2 failed\n");

  if((unsigned char)test2 == 0xFF)
    printf("check 3 passed\n");
  else
    printf("check 3 failed\n");
  printf("%d \n", (unsigned char) 0xFF);
  printf("%u \n", 0xFF);
  printf("%d \n", 0xFF);
  printf("%d \n", test2);
  printf("%u \n", test2);
  printf("%d \n", (unsigned char) test2);
  printf("%u \n", (unsigned) test2);
  printf("%u \n", (unsigned char) test2);
  printf("%u \n", (unsigned char) 0x100);
  printf("%u \n", 0x100);
  printf("%d \n", test3);
  printf("%d \n", (unsigned char) test3);
  printf("%u \n", (unsigned char) test3);
  return 0;
}
