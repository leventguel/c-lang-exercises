#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() 
{
  printf("sizeof(char) = %lu\n", sizeof(char));
  printf("sizeof(char *) = %lu\n", sizeof(char *));
  printf("sizeof(void *) = %lu\n", sizeof(void*));
  printf("sizeof(wchar_t) = %lu\n", sizeof(wchar_t));

  printf("sizeof(short) = %lu\n", sizeof(short));
  printf("sizeof(int) = %lu\n", sizeof(int));
  printf("sizeof(float) = %lu\n", sizeof(float));
  printf("sizeof(double) = %lu\n", sizeof(double));
  printf("sizeof(long int) = %lu\n", sizeof(long int));
  printf("sizeof(long double) = %lu\n", sizeof(long double));
  printf("sizeof(long long int) = %lu\n", sizeof(long long int));

  printf("sizeof(unsigned) = %lu\n", sizeof(unsigned));
  printf("sizeof(size_t) = %lu\n", sizeof(size_t));
  printf("sizeof(ssize_t) = %lu\n", sizeof(ssize_t));
  exit(0);
}

