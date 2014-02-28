#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
int main(void)
{
  int len1, len2;
     
  const char *src = "abcd";
  len1 = strlen(src) + 1;

  const char *src2 = "efghijklmnoöp";
  len2 = strlen(src2) + 1;
     
  char *s = NULL;

  if((s = calloc(len1, sizeof(char))) != NULL)
    {
      strcpy(s, src);

      char *m = NULL;

      if(( m = realloc(m, len2 * sizeof(char))) != NULL)
	{
	  strcpy(m, src2);
	  
	  char *both = NULL;

	  if((both = realloc(both, (len1+len2) * sizeof(char))) != NULL)
	    {
	      printf("%s\n", s);
	      printf("%s\n", m);
	      strcpy(both, s);
	      *(both+len1-1) += ' ';
	      strcpy((both+len1), m);
	      printf("%s\n", both);
	      free(both);
	      free(m);
	      free(s);
	    }
	}
      else
	{
	  printf("error, reallocation failed\n");
	}
    }
  else
    {
      printf("allocation failed\n");
    }

  return 0;
}
