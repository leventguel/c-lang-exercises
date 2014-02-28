#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <limits.h>
#include <wchar.h>

static void print_char_page(const char *locale, int max)
{
  int c;
  char *loc;

  if (NULL != (loc = setlocale(LC_CTYPE, NULL)) )
    {
      printf("locale changed from '%s', ", loc);
    }

  if (NULL != (loc = setlocale(LC_CTYPE, locale)) )
    {
      printf("to: '%s'\n", loc);
    }

  printf("+----+-----+---+\n");
  printf("|Hex | Dec |Car|\n");
  printf("+----+-----+---+\n");
  for (c=0; c<max; c++)
    {
      if ( isprint(c) )
	{
	  printf("| %02x | %3d | %c |\n", c, c, c);
	}
    }
}

int main(void)
{
  /* change env to locale-specific native environment.*/
  print_char_page("", WCHAR_MAX);

  return 0;
}
