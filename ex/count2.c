#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  const char *string="jel3333Lol0122";
  int len = strlen(string)+1;
  printf("\nstring: %s, length: %d\n", string, len);

  int cnts[256]={0};
  const char *c = {0};

  for (c=string; *c!=0; ++c) 
    {
      cnts[(int)*c]++;
    }
  
  int i;
  for (i=0; i < 256; ++i) 
    { 
      if (cnts[i] > 0)
	{ 
	  printf("\n%c -> %d", i, cnts[i]);
	}
      
    }
  
  printf("\n\n");
  return 0;
}
