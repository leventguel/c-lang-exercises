#include <stdio.h>
#include <stdint.h>
#include <locale.h>

int main(void) {
  setlocale(LC_ALL, "");
  uint32_t c;
  for (c = 8192; c <= 9216; c++) printf("0x%x: %lc\n", c, c);
  printf("\n");
  return 0;
}
