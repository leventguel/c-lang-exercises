#include <stdio.h>
#include <stdint.h>
#include <locale.h>

int main(void) {
  setlocale(LC_ALL, "");
  int c;
  char d[4];
  d=c;
  for (c = 8192; c <= 9216; c++) printf("0x%x: %c%c%c%c\n", (unsigned int)c, (int)d[0],(int)d[1],(int)d[2],(int)d[3]);
  printf("\n");
  return 0;
}
