#include <stdio.h>

int main(void)
{
  
  auto int i = 1;

  {
    auto int i = 2;
    
    {
      auto int i = 3;
      printf("%d ", i);
    }
    
    printf("%d ", i);
  }
  printf("%d \n", i);
  return 0;
}
