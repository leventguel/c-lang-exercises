#include <stdio.h>
#include <stdlib.h>

#define i 6
#define j 6

int main()
{

  int r;
  int c;

  int array[i][j];

  char d;
  for(d=97; d<=124; ++d)
    for(r=0; r < i; r++)
      for(c=0; c < j; c++)
	{
	  array[r][c+1] = 0;
	  array[r-1][c] = 0;
	  array[r][c-1] = 0;
	  array[r-1][c-1] = d++;
	  array[r][c] = 0;
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
