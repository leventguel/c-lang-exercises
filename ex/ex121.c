#include <stdio.h>

int main(void)
{
  char c;
  
  while((c=getchar()) != EOF)
    {
      if(c >= 'A' && c <= 'Z')
	c = c - 'A' + 'a';
      putchar(c);
    }
  return 0;
}
