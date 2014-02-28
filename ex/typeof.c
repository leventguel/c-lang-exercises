#include <stdio.h>

#define pointer(T)  (typeof(T *))
#define array(T, N) (typeof(T [N]))

/* This declares y with the type of what x points to.
 * typeof (*x) y; */

/* This declares y as an array of such values.
 * typeof (*x) y[4]; */

/* This declares y as an array of pointers to characters:
 * typeof (typeof (char *)[4]) y; */

/* It is equivalent to the following traditional C declaration:
 * char *y[4]; */

/* Now the declaration can be rewritten this way:
 * array (pointer (char), 4) y;
 * Thus, array (pointer (char), 4) is the type of arrays of 4 pointers to char. */

/* effect of declaring T to have the type of the expression expr: (new version for all versions of gcc) typedef typeof(expr) T; */

char x = 'a', y = 'b', z = 'c', t = 'd'; /* four chars */

char *a =  (char *) &x;
char *b =  (char *) &y;
char *c =  (char *) &z;
char *d =  (char *) &t;
/* four pointers to chars */
/* notice the & operator returns something different than a char, thus the need for a cast ! */

char **k = (char **) &a;
char **l = (char **) &b;
char **m = (char **) &c;
char **n = (char **) &d;

int i; /* counter */

int main(void)
{

  typeof (typeof (char *) [5]) y = {a, b, c, d, 0};

  for(i = 0; i < 4; i++)
    {
      printf("*y[i]: %d \n", (int) *y[i]);
    }

  printf("\n");

  for(i = 0; i < 4; i++)
    {
      printf("*y[i]: %c \n", *y[i]);
    }
  
  printf("\n");

  printf("*y: %s \n", *y);

  printf("\n");
  
  typeof (typeof (char **)[5]) e = {k, l, m, n, 0};

  for(i = 0; i < 4; i++)
    {
      printf("**e[i]: %d \n", (int) **e[i]);
    }
  
  printf("\n");

  for(i = 0; i < 4; i++)
    {
      printf("**e[i]: %c \n", (char) **e[i]);
    }

  printf("\n");

  printf("**e: %s \n", **e);
  printf("**e: %s ", *e[0]);

  return 0;
}
