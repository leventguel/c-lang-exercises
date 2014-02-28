#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;
  printf("\nthe main program process ID is %d\n", (int) getpid ());

  child_pid = fork();

  if (child_pid != 0) {
    printf("\nthis is the parent process, with id %d\n", (int) getpid ());
    printf("the child’s process ID is %d\n\n", (int) child_pid);
  }
  else
    printf("\nthis is the child process, with id %d\n\n", (int) getpid ());
  return 0;
}
