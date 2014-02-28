#include <stdio.h>

int main(void)
{

  const int two=2;
  const int i = two;
  switch(two)
    {
    case 2: printf("case 2 \n");
    default: break;
    }

  switch(i)
    {
    case 2: printf("case 2 \n");
    default: break;
    }

  return 0;
}
