#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_number)
{
  /* Clean up the child process */
  int status;
  wait(&status);
  /* Store it's exit status in a global variable */
  child_exit_status = status;
}

 /* Spawn a child process running a new program. PROGRAM is the name
of the program to run; the path will be searched for this program.
ARG_LIST is a NULL-terminated list of character strings to be
passed as the program’s argument list. Returns the process ID of
the spawned process. */
int spawn (char* program, char** arg_list)
{
  pid_t child_pid;
  /* Duplicate this process. */
  child_pid = fork ();
  if (child_pid != 0)
    /* This is the parent process. */
    return child_pid;
  else {
    /* Now execute PROGRAM, searching for it in the path. */
    execvp (program, arg_list);

    /* The execvp function returns only if an error occurs. */
    fprintf (stderr, "an error occurred in execvp\n");
    abort ();
  }
}

int main () {
  /* Hanlde SIGCHLD by calling clean_up_child_process */
  struct sigaction sigchld_action;
  memset(&sigchld_action, 0, sizeof(sigchld_action));
  sigchld_action.sa_handler = &clean_up_child_process;
  sigaction(SIGCHLD, &sigchld_action, NULL);

  /* The argument list to pass to the “ls” command. */
  char* arg_list[] = {
    "ls",
    /* argv[0], the name of the program. */
    "-l",
    ".",
    NULL
    /* The argument list must end with a NULL. */
  };
  
  /* Spawn a child process running the “ls” command.
     returned child process ID. */
  spawn ("ls", arg_list);

  printf ("\ndone with main program\n");
  printf ("child_exit_status: %d\n", child_exit_status);
  printf("\n");
  return 0;
}
