#include <stdio.h>

int main(void)
{
  printf("\nVariables of type char occupy %lu bytes", sizeof(char));
  printf("\nVariables of type short occupy %lu bytes", sizeof(short));
  printf("\nVariables of type int occupy %lu bytes", sizeof(int));
  printf("\nVariables of type long occupy %lu bytes", sizeof(long));
  printf("\nVariable of type float occupy %lu bytes", sizeof(float));
  printf("\nVariables of type double occupy %lu bytes", sizeof(double));
  printf("\nVariables of type long double occupy %lu bytes", sizeof(long double));
  printf("\n");
  return 0;
}

