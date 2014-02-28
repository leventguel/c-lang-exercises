#include <stdio.h>
#include <stdlib.h>

static void bit_pat(long long int);

static void bit_pat(long long int n)
{
  long long int m,i;
  for(i=15; i>=0; i--)
    {
      m=1<<i;
      if((n&m)==0)
	{
	  printf("0");
	}
      else
	{
	  printf("1");
	}
    }
}

int main(int argc, char **argv)
{
  static long long int i = 0;

  if (argc < 2) 
    {
      while (scanf("%lld", &i) == 1)
	{
	  printf("bit_pattern is: \n");
	  bit_pat(i);
	  printf("\n");
	}
    }

  else 
    {                                                                                                                                             
      for (i=1; i<argc; i++) 
	{
	  printf("bit pattern is: \n");
	  bit_pat((long long int) atoi(argv[i]));
	  printf("\n");
	}
    }
  
  return 0;
}
