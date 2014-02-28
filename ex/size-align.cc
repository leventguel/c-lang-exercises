#include <iostream>
 
using namespace std;
 
template <typename T>
void print (char const* name)
{
  cerr << name
       << " sizeof = " << sizeof (T)
       << " alignof = " << __alignof__ (T)
       << endl;
}
 
int main ()
{
  print<bool>        ("bool          ");
  print<wchar_t>     ("wchar_t       ");
  print<short>       ("short int     ");
  print<int>         ("int           ");
  print<long>        ("long int      ");
  print<long long>   ("long long int ");
  print<float>       ("float         ");
  print<double>      ("double        ");
  print<long double> ("long double   ");
  print<void*>       ("void*         ");
}
