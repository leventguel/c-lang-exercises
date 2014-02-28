#include <stdio.h>
#include <stdlib.h>

#define i 5
#define j 5

int main()
{

  int r;
  int c;

  int array[i][j];

  char d;
  for(d=97; d<=122; ++d)
    for(r=0; r<i; r++)
      for(c=0; c<j; c++)
	{
	  array[r][c] = d++;
	}

  int arraysz = sizeof(array)/sizeof(array[0]);


  printf("\nElements: \n");
  
  for(r = 0; r <= arraysz -1; r++)
    for(c = 0; c <= arraysz -1; c++)
      {
	printf("%c ", array[r][c]); 
      }

  printf("\n\nColumns: \n");
  printf("{ ");

  for(r=0; r <= arraysz -1; r++)
    {
      for(c = 0; c <= arraysz -1; c++)
	{
	    printf("%c ", array[c][r]);

	}
    }

  printf("}");

  printf("\n\nRows: \n");
  printf("{ ");

  for(c=0; c <= arraysz -1; c++)
    {
      for(r = 0; r <= arraysz -1; r++)
	{
	  printf("%c ", array[c][r]);
	}
    }

  printf("}");

  
  printf("\n\nsize of array %d \n", arraysz);
  return 0;
}
