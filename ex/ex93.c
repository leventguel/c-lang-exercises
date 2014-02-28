#include <stdio.h>
#include <stdlib.h>

int sum; /* This is a global variable */
int sumsq; /* another global */

void header() /* This is the function named header */
{
  sum = 0; /* initialize the variable "sum" */
  sumsq = 0;
  printf("This is the header for the square program\n\n");
}

int square(number)   /* This is the square function */
int number;
{
  int numsq;
  numsq = number * number; /* This produces the square */
  sum += number; /* This produces the sum of the numbers */
  sumsq += numsq; /* This produces the sum of the squares */
  printf("The square of %d is %d\n",number,numsq);
  return 0;
}

void ending() /* This is the ending function */
{
  printf("\nThis is the footer for the square programm\n\n");
  printf("\nThe sum of the numbers is %d\n", sum);
  printf("\nThe sum of the squares is %d\n\n", sumsq);
}


int main(int argc, char **argv)
{
  int i;
  int index;
  header(); /* This calls the function named header */

  if (argc < 2)
    {
      while(scanf("%d", &i) == 1) 
	for (index = 1;index <= i;index++)
	  square(index); /* This calls the square function */
    }
  
  else
    {
      for(i=1; i < argc; i++)
	for(index=1; index <= atoi(argv[i]); index++) /* argv[i] is a (char *) else, and then you have to deref the array manually! */
	  square(index);
    }

  ending(); /* This calls the ending function*/
  return 0;
}
