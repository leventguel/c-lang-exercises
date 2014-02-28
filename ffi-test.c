#include <stdio.h>
#include <ffi.h>

int main ()
{
  printf ("&ffi_type_ulong: %p &ffi_type_uint32: %p\n", 
          &ffi_type_ulong, &ffi_type_uint32);
}
