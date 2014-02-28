#include <wchar.h>

int main() {
  int i;
  char c[20] = {"hellow, world wide!"};
  wchar_t wc[20];
  mbstate_t state = {0};
  size_t result;

  for(i=0; i<20; i++)
    {
      result = mbrtowc(&wc[i], &c[i], 1, &state);
      wprintf(L"%lc ", wc[i]);
    }
  
  wprintf(L"\n");
  return 0;
}
