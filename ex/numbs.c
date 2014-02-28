#include <stdio.h>

int main () {
  int num = 0;
  while (getchar() != EOF) {
    printf("%d\n", ++num);
  }
  return 0;
}


