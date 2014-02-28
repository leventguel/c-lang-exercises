#include <stdio.h>

int triangleNumber(int);
int i, num, result;

int main(void)
{
  printf("provide a number: ");
  scanf("%d", &num);
  printf("the %d.th triangular number is: %d\n", num, triangleNumber(num));
  return 0;
}

int triangleNumber(int num)
{
  int sumnum=0;
  for(i=0; i<=num;i++)
    {
      sumnum += i;
    }
  return sumnum;
}
