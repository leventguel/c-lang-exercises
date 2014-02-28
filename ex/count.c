#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  int i = 0, j=0, uppercase_counter, lowercase_counter, number_counter, k, m, l, len_alphabet=26;
  char lowercase = 'a';// == 97
  char uppercase = 'A';
  const char *string="jel3333Lol0122";
  int str_len=strlen(string)+1;
  printf("\nstring: %s, length: %d\n", string, str_len);
    
  for(j=0; j < len_alphabet; j++)
    {
      lowercase_counter=0;
      uppercase_counter=0;
      number_counter=0;
      k=0;
      m=0;
      l=0;
      for (i = 0; string[i]!=0; i++)
	{
	  if ((string[i]) == (lowercase+j))
	    {
	      lowercase_counter++;
	      k=1;
	    }

	  if((string[i]) == (uppercase+j))
	    {
	      uppercase_counter++;
	      m=1;
	    }

	  if((string[i]) == ('0'+j))
	    {
	      number_counter++;
	      l=1;
	    }
	}
      
      if((k==1))
	{
	  printf("\n%c -> %d", (lowercase+j), lowercase_counter);
	}
      
      if((m==1))
	{
	  printf("\n%c -> %d", (uppercase+j), uppercase_counter);
	}

      if((l==1))
	{
	  printf("\n%c -> %d", ('0'+j), number_counter);
	}
    }
  
  printf("\n\n");
  return 0;
}
