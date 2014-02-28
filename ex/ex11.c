#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  // go through each string in argv
  // why am I skipping argv[0]?
  for(i = (argc -1); i >= 1; i--) {
    printf("arg %d: %s\n", i, argv[i]);
  }

  // let's make our own array of strings
  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };
  int num_states = 4;

  for(i = (num_states - 1); i >= 0; i--) {
    printf("state %d: %s\n", i, states[i]);
  }

  return 0;
}
