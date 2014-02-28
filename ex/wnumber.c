#include <wchar.h>

int main() {
  const char *c[] = {"hellow, world wide! 11"};
  int d=65;
  char h='A';
  wchar_t wd;
  wchar_t wc[23];
  static mbstate_t state;

  mbsrtowcs(wc, c, 23, &state); /* wide string */
  mbrtowc(&wd, &h, 1, &state); /* wide char */
  wprintf(L"%ls\n", wc); /* wide string */
  wprintf(L"%lc\n", wd); /* wide-char wide*/
  wprintf(L"%hc\n", wd); /* wide-char non-wide */ 
  wprintf(L"%ld\n", wd); /* integer wide*/
  wprintf(L"%hd\n", d); /* integer non-wide*/

  return 0;
}
