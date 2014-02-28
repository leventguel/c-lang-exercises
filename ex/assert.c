#define CompilerAssert(exp) extern char _CompilerAssert[(exp)?1:-1]

int main(void)
{
  /*--- A forced CompilerAssert ---*/
  long lVal;
  CompilerAssert(sizeof(lVal)==0);
  return 0;

} /* main */
 
