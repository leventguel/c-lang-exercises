#include <stdio.h>
#include <stdlib.h>

#define i 3
#define j 3

int main()
{

  /* int **array1 = malloc(nrows * sizeof(int *));

   *for(i = 0; i < nrows; i++)
   *array1[i] = malloc(ncolumns * sizeof(int)); */
    
  int array[i][j] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

  int arraysz = sizeof(array)/sizeof(array[0]);

    {
      printf("\nElements: \n");
      printf("0,0: %d \n", array[0][0]);
      printf("0,1: %d \n", array[0][1]);
      printf("0,2: %d \n", array[0][2]);
      
      printf("1,1: %d \n", array[1][0]);
      printf("1,2: %d \n", array[1][1]);
      printf("1,2: %d \n", array[1][2]);
      
      printf("2,0: %d \n", array[2][0]);
      printf("2,1: %d \n", array[2][1]);
      printf("2,2: %d \n", array[2][2]);
      
      printf("\nRows: \n");
      printf("\n1.st row {%d %d %d} \n", array[0][0], array[0][1], array[0][2]);
      printf("\n2.nd row {%d %d %d} \n", array[1][0], array[1][1], array[1][2]);
      printf("\n3.rd row {%d %d %d} \n", array[2][0], array[2][1], array[2][2]);
      
      printf("\nColumns: \n");
      printf("\n1.st col\n\n{%d \t%d \t%d} \n", array[0][0], array[1][0], array[2][0]);
      printf("\n2.nd col\n\n{%d \t%d \t%d} \n", array[0][1], array[1][1], array[2][1]);
      printf("\n3.rd col\n\n{%d \t%d \t%d} \n", array[0][2], array[1][2], array[2][2]);
    }

  
  printf("\nsize of array %d \n", arraysz);
  return 0;
}
