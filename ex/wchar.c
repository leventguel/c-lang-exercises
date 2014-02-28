#include <wchar.h>

int main(void)
{
  wprintf(L"%hs", "printf1\n");
  wprintf(L"%ls", L"wprintf\n");
  wprintf(L"%hs", "printf2\n");
  return 0;
}
