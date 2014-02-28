#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void) {
  setlocale(LC_ALL, "");
  wchar_t c;
  for (c = 8192; c <= 9216; c++) wprintf(L"0x%x: %lc \n", c);
  printf("\n");
  return 0;
}
