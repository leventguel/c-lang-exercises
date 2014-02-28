int main(void) {
  long eax;
  short bx;
  char cl;

  int foo=10;
  
  __asm__("nop;nop;nop"); // to separate inline asm from the rest of
  // the code					

  //  __asm__("test %%eax, %%eax" : /* no output */ : "eax"(foo));

  __asm__ __volatile__("test %0,%0; test %1,%1; test %2,%2" : /* no outputs */ : "a"((long)eax), "b"((short)bx), "c"((char)cl));
  
  __asm__("nop;nop;nop");
  return 0;
}
