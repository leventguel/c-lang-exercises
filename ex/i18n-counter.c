/* Non-executable part */
#include <stdio.h>
#include <ctype.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define _(str) gettext (str)
#define gettext_noop(str) (str)
#define N_(str) gettext_noop(str)

int main() {
  int i, length, counter=0;

  char *mess, line[11], *info[]={ N_ ("digit"), N_ ("digits")};

  /* Executable part */
  setlocale(LC_ALL,"");

  bindtextdomain ("counter", ".");

  textdomain ("counter");

  printf(_("Please, type a line\n"));

  fgets(line,11,stdin);

  length=strlen(line);

  for(i=0; i<length; i++) {
    counter+=isdigit(line[i])?1:0;

    mess=counter>1?info[1]:info[0];

    printf (_("You typed %d %s\n"), counter,_(mess));
    exit(0); }
}
