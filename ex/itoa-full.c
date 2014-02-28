#include <stdio.h>

/* Custom reverse() function for which the length of the string is
 * known in advance (avoids a call to strlen() and including 
 * string.h).
 *
 * @args: a null-terminated string
 * @return: nothing
 * @result: the characters in str are reversed
 */
void reverse(char* str, int length){
  int i = 0, j = length-1;
  char tmp;
  while (i < j) {
    tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++; j--;
  }
}

/* Returns the string representation of integer n. Assumes 32-bit
 * int, and 8-bit bytes (i.e. sizeof(char) = 1, sizeof(int) = 4).
 * Assumes char *out is big enough to hold the string 
 * representation of n.
 *
 * @args: int n to convert, char* out for the result
 * @result the string representation of n is stored in out
 * @return 0 on success, -1 on error
 */
int itoa(int n, char* out)
{
  // if negative, need 1 char for the sign
  int sign = n < 0? 1: 0;
  int i = 0;
  if (n == 0) {
    out[i++] = '0';
  } else if (n < 0) {
    out[i++] = '-';
    n = -n;
  }
  while (n > 0) {
    out[i++] = '0' + n % 10;
    n /= 10;
  }
  out[i] = '\0';
  reverse(out + sign, i - sign);
  return 0;
}


/* Test itoa() correctness
 */
int main()
{
  int test1 = -112993, test2 = 0, test3 = -1, test4 = 6;
  // for 32-bit ints, the max # of characters is: one '-' sign, 
  // 10 digits, one null terminator = 12 chars.
  char result[12];
  itoa(test1, result);
  printf("itoa(%d) is %s\n", test1, result);
  itoa(test2, result);
  printf("itoa(%d) is %s\n", test2, result);
  itoa(test3, result);
  printf("itoa(%d) is %s\n", test3, result);
  itoa(test4, result);
  printf("itoa(%d) is %s\n", test4, result);
  return 0;
}
