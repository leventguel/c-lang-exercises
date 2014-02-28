#include <stdio.h>
#include <stdlib.h>

#define i 3
#define j 3

int main()
{

  int r;
  int c;

  /* int **array1 = malloc(nrows * sizeof(int *));

   *for(i = 0; i < nrows; i++)
   *array1[i] = malloc(ncolumns * sizeof(int)); */
    
  int array[i][j] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

  int arraysz = sizeof(array)/sizeof(array[0]);


  printf("\nElements: \n");
  
  for(r = 0; r <= arraysz -1; r++)
    for(c = 0; c <= arraysz -1; c++)
      {
	printf("%d ", array[r][c]); 
      }

  printf("\n\nRows: \n");
  printf("{ ");

  for(r=0; r <= arraysz -1; r++)
    {
      for(c = 0; c <= arraysz -1; c++)
	{
	    printf("%d ", array[r][c]);

	}
    }

  printf("}");

  printf("\n\nColumns: \n");
  printf("{ ");

  for(c=0; c <= arraysz -1; c++)
    {
      for(r = 0; r <= arraysz -1; r++)
	{
	  printf("%d ", array[r][c]);
	}
    }

  printf("}");

  
  printf("\n\nsize of array %d \n", arraysz);
  return 0;
}
