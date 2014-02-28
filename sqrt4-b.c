unsigned int sqrt32(unsigned long n)  
{  
  unsigned int c = 0x8000;  
  unsigned int g = 0x8000;  
      
  for(;;) {  
    if(g*g > n)  
      g ^= c;  
    c >>= 1;  
    if(c == 0)  
      return g;  
    g |= c;  
  }  
}  
