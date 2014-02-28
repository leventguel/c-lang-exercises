#include <stdio.h>

int main(void)
{

  int i; /* This is not c++! */
  i(3);

  int j(4); /* This is not c++, this won't work too! */

  printf("%d %d", i, j);
  return 0;
}
