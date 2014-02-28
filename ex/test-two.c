#include <stdio.h>

int main (int argc, char *argv[])
{

  int i; 
  int num_states = 4;

  for(i = num_states; i > 0; i--) {
    printf("state: %d \n", i);
  }
  return 0;
}
