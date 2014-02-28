#include <stdio.h>
#include <string.h>

int main(void)
{
  char s[4];
  long i;
  char *s2;

  strcpy(s, "Jim");
  i = (long) s;
  printf("i = %ld (0x%lx)\n", (long) i, (long) i);
  printf("s = %ld (0x%lx)\n", (long) s, (long) s);

  i++;
  s2 = (char *) i;
  printf("s = 0x%lx.  s2 = 0x%lx, i = 0x%lx, s[0] = %c, s[1] = %c, *s2 = %c\n",
	 (long) s, (long) s2, i, s[0], s[1], *s2);
  return 0;
}
