#include <stdio.h>
#include <string.h>

void itochar(int x, char *buffer, int radix);

int main()
{
  char buffer[10];
  itochar(64, buffer, 10);
  printf ("\n %s \n", buffer);
  return 0;
}

void strrev(char *str) { 
  char temp, *end_ptr;
  if( str == NULL || !(*str) ) return;
  end_ptr = str + strlen(str) - 1;

  while( end_ptr > str ) 
    { 
      temp = *str; 
      *str = *end_ptr; 
      *end_ptr = temp; str++; 
      end_ptr--; 
    } 
}


void itochar(int x, char *buffer, int radix)
{
  int i = 0, n = 0, s = 0;

  while (n > 0)
    {
      s = n%radix;
      n = n/radix;
      buffer[i++] = '0' + s;
    }
  buffer[i] = '\0';
  strrev(buffer);
}
