#include <stddef.h>
#include <stdio.h>

int main(void)
{
  wchar_t w_ch = L'A';
  
  w_ch = 0;

  scanf("%lc", &w_ch);
  printf("you entered: %lc \n", w_ch);
  return 0;
}
