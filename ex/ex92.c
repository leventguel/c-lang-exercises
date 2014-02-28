int main(void) /* this file will illustrate logical compares */
{
  int x = 11,y = 11,z = 11;
  char a = 40,b = 40,c = 40;
  float r = 12.987,s = 12.987,t = 12.987;

  /* First group of compare statements */

  if  (x == y) z = -13;
  if  (x > z) a = 'A';
  if (!(x > z)) a = 'B';
  if (b <= c) r = 0.0;
  if (r != s) t = c/2;

  /* second group */

  if (x = (r != s)) z = 1000;
  if (x = y) z = 222;
  if (x != 0) z = 333;
  if (x) z = 444;

  /* third group */
  
  x = y = z = 77;
  if ((x == y) && (x == 77)) z = 33;
  if ((x >y) || (z > 12)) z = 22;
  if (x && y && z) z = 11;
  if ((x = 1) && (y = 2) && (z = 3)) r = 12.00;
  if ((x == 2) && (y = 3) && (z = 4)) r = 14.56;

  /* fourth group */
  
  if (x == x); z = 27.345;
  if (x != x) z = 27.345;
  if (x = 0) z = 27.345;

  return 0;
}
