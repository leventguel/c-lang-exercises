#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

// NOTE: *NOT* thread safe, not re-entrant
const char* unicode_to_utf8(wchar_t c)
{
  static unsigned char b_static[5];
  unsigned char* b = b_static; 

  if (c<(1<<7))// 7 bit Unicode encoded as plain ascii
    {
      *b++ = (unsigned char)(c);
    }
  else if (c<(1<<11))// 11 bit Unicode encoded in 2 UTF-8 bytes
    {
      *b++ = (unsigned char)((c>>6)|0xC0);
      *b++ = (unsigned char)((c&0x3F)|0x80);
    }
  else if (c<(1<<16))// 16 bit Unicode encoded in 3 UTF-8 bytes
    {
      *b++ = (unsigned char)(((c>>12))|0xE0);
      *b++ =  (unsigned char)(((c>>6)&0x3F)|0x80);
      *b++ =  (unsigned char)((c&0x3F)|0x80);
    }

  else if (c<(1<<21))// 21 bit Unicode encoded in 4 UTF-8 bytes
    {
      *b++ = (unsigned char)(((c>>18))|0xF0);
      *b++ = (unsigned char)(((c>>12)&0x3F)|0x80);
      *b++ = (unsigned char)(((c>>6)&0x3F)|0x80);
      *b++ = (unsigned char)((c&0x3F)|0x80);
    }
  *b = '\0';
  return b_static;
}


int main() {
  int r;
  wchar_t myChar1 = L'Ω';
  r = printf("char is %s\n", unicode_to_utf8(myChar1));
  return 0;
}
