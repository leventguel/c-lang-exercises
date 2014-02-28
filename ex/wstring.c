#include <wchar.h>

int main() {
  const char *c[] = {"hellow, world wide!"};
  wchar_t wc[20];
  static mbstate_t state;

  mbsrtowcs(wc, c, 20, &state);
  wprintf(L"%ls", wc);
  

  wprintf(L"\n");
  return 0;
}
