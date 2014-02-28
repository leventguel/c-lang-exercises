#include <stdio.h>

struct {
  unsigned int a: 8;
} bits = {255};
 
int main(void) {
  printf("bits.a = %d.\n", bits.a);
  return 0;
}
