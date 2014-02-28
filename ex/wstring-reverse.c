#include <wchar.h>

int main(void)
{

  char str[] = "Test String";
  const char *d=str;
  const char **m=&d;
  char *s = str, *e = str+sizeof(str)-2;
  wchar_t wc[sizeof(str)];
  static mbstate_t state;


  while(s<e) 
    { 
      char c = *s;
      *s= *e; 
      *e = c; 
      s++;e--;
    }

  mbsrtowcs(wc, m, sizeof(str), &state);
  wprintf(L"%ls\n", wc);

  return 0;
}
