
#include "comb/composition-nz-restrpref.h"

#include "comb/comb-print.h"

#include "comb/is-unimodal.h"
#include "comb/is-smooth.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts with restricted prefixes.
//% Lexicographic order.

// Cf. comb/composition-nz-demo.cc for all compositions

//#define TIMING  // uncomment to disable printing

bool cond_true(const ulong *, ulong)
{ return true; }
// -------------------------

bool cond_false(const ulong *, ulong)
{ return false; }
// -------------------------

bool cond_dist(const ulong *a, ulong k)
// Adjacent parts distinct.
// Carlitz compositions, A003242. A003242
{
    if ( k==0 )  return true;
    return ( a[k] != a[k-1] );
}
// -------------------------

bool cond_consec(const ulong *a, ulong k)
// Partitions into consecutive integers.
// A001227 (odd divisors of n)).
{
    if ( k==0 )  return true;
    return  ( a[k] == a[k-1] + 1 );

//    return  ( a[k] == a[k-1] + 2 );  // A038548 Number of divisors <= sqrt(n).
}
// -------------------------

bool cond_updown(const ulong *a, ulong k)
// compositions with alternating increases and decreases:
// A025047 (and A025048, A025049).
{
    if ( k==0 )  return true;
    if  ( a[k] == a[k-1] )  return false;
    if ( k <= 1 )    return true;
    return ( (a[k-2] < a[k-1]) != (a[k-1] < a[k-0]) );
}
// -------------------------

bool cond_odd(const ulong *a, ulong k)
// Compositions into odd parts:
// A000045 (Fibonacci numbers).
{
    return  ( 1 == ( a[k] & 1UL ) );
//    return ( a[k] <= 2 );  // also Fibonacci
//    return ( a[k] >= 2 );  // also Fibonacci (A212804)
}
// -------------------------


bool cond_smooth(const ulong *a, ulong k)
// Absolute differences <= 1:  A034297.
{
    if ( k==0 )  return true;
    ulong d = a[k] - a[k-1];
    if ( (long)d < 0 ) d = -d;
    return ( d <= 1 );
}
// -------------------------

bool cond_smooth_part(const ulong *a, ulong k)
// Flat partitions: differences <= 1:  A034296.
{
    if ( k==0 )  return true;
    ulong d = a[k-1] - a[k];
    if ( (long)d < 0 )   return false;
    return ( d <= 1 );  // A034296
//    return ( d <= 2 );  // A224956
}
// -------------------------

bool cond_superdiag(const ulong *a, ulong k)
// a[k] > k:  A219282.
{
    return ( a[k] > k );
}
// -------------------------


bool cond_subdiag(const ulong *a, ulong k)
{
    return  ( a[k] <= k+1 );   // A008930
}
// -------------------------


bool cond_par_diff(const ulong *a, ulong k)
// Parities of adjacent part different: A062200
{
    if ( k==0 )  return true;
    return ( ((a[k]^a[k-1]) & 1) ==1 );
}
// -------------------------

bool cond_asc(const ulong *a, ulong k)
// Partitions as non-decreasing lists: A000041.
{
    if ( k==0 )  return true;
    return  ( a[k] >= a[k-1] );
}
// -------------------------

bool cond_desc(const ulong *a, ulong k)
// Partitions as non-increasing lists: A000041.
{
    if ( k==0 )  return true;
    return  ( a[k] <= a[k-1] );
}
// -------------------------

bool cond_growth(const ulong *a, ulong k)
// part(k) <= 2 * part(k-1):  A002843
{
    if ( k==0 )  return true;
    return  ( a[k] <= 2*a[k-1] );
}
// -------------------------

bool cond_fall(const ulong *a, ulong k)
// 2*part(k) <= part(k-1):  A000929
{
    if ( k==0 )  return true;
    return  ( 2*a[k] <= a[k-1] );
//    return  ( a[k] >= 2* a[k-1] );  // same ascending
//    return  ( 3*a[k] <= a[k-1] );  // A132011
}
// -------------------------

bool cond_change(const ulong *a, ulong k)
// Bounded change (cond_fall && cond_growth):  A224957
{
    if ( k==0 )  return true;
    if  ( a[k] > 2*a[k-1] )  return false;  // this only ==> A002843
    if  ( 2*a[k] < a[k-1] )  return false;  // this only ==> A002843
    return true;
}
// -------------------------

bool cond_mers_desc(const ulong *a, ulong k)
// s-partitions: partitions into Mersenne numbers: A000929
{
    ulong x = a[k];
    if ( !!(x & (x+1)) )  return false;
    if ( k==0 )  return true;
    return ( x<=a[k-1] );
}
// -------------------------


bool cond_mers(const ulong *a, ulong k)
// parts are Mersenne numbers: A104977 (absolute values)
{
    ulong x = a[k];
    return !(x & (x+1));
}
// -------------------------

bool cond_2pow(const ulong *a, ulong k)
// parts are powers of 2:  A023359
// As partitions: A018819, cf. A000123
{
    ulong x = a[k];
    return !(x & (x-1));
}
// -------------------------


bool cond_first_max(const ulong *a, ulong k)
{
    if ( k==0 )  return true;
//    return ( a[k] <= a[0] );  // first part max: A007059, A079500
    return ( a[k] < a[0] );  // first part strictly max: A007059
//    return  ( a[k] <=  a[0] + 1 );  // A048888
}
// -------------------------

bool cond_first_min(const ulong *a, ulong k)
{
    if ( k==0 )  return true;
    return ( a[k] >= a[0] );  // first part min: A171682
//    return ( a[k] > a[0] );  // first part strictly min: A079501
//    return  ( a[k] >=  a[0] - 1 );  // A224960
}
// -------------------------

bool cond_min(const ulong *a, ulong k)
{
    return  ( a[k] >= 2 );  // A000045 a(n)=a(n-1)+a(n-2)
//    return  ( a[k] >= 3 );  // A000930 a(n)=a(n-1)+a(n-3)
//    return  ( a[k] >= 4 );  // A003269 a(n)=a(n-1)+a(n-4)
}
// -------------------------

bool cond_no_3prog(const ulong *a, ulong k)
// No 3 consecutive parts in arithmetic progression: A000000
{
    if ( k!=0 )  if ( a[k]>a[k-1] )  return false;  // partitions: A000000

    if ( k<=1 )  return true;
    ulong d1 = a[k] - a[k-1];
    ulong d2 = a[k-1] - a[k-2];
    return ( d1 != d2 );
}
// -------------------------

bool cond_2dist(const ulong *a, ulong k)
// part(k) != part(k-2):
// Partitions: A000726; compositions A224958.
{
//    if ( k!=0 )  if ( a[k]>a[k-1] )  return false;  // partitions: A000726
    if ( k<=1 )  return true;
    return ( a[k] != a[k-2] );
}
// -------------------------

bool cond_up_step(const ulong *a, ulong k)
// Limited up-steps
{
    if ( k==0 )  return true;
    if ( a[k] > a[k-1] )  return ( (a[k] - a[k-1]) <= 1 );  // A003116
//    if ( a[k] > a[k-1] )  return ( (a[k] - a[k-1]) <= 2 );  // A224959
    return true;
}
// -------------------------


bool cond_test(const ulong *a, ulong k)
{
    if ( k==0 )  return ( a[k]==1 );  //A002083
    ulong s =0;
    for (ulong j=0; j<k; ++j)  s += a[j];
    return ( a[k] <= s );

//    if ( k==0 )  return true;  // no two adjacent non-ones A005251
//    return ( (a[k]==1) || (a[k-1]==1) );

//    if ( k==0 )  return ( 0==(a[0]%2) );  // first part even/odd: A001045
//    if ( a[k] > a[k-1] )  return false;  // A027187 (even), cf. A027193 (odd)
//    return true;

//    return ( a[k]!=k );  // A000000
//    return ( a[k]!=k+1 );  // A000000

//    return  ( a[k] <= k + a[0] );  // A000000
//    return  ( a[k] <= 2*a[0] );  // A000000
//    return  ( a[k] <= a[0] + 1 );  // A048888
//    return  ( a[k] <= a[0] + 2 );  // A000000
//    return  ( a[k] <= (k+1)*a[0] );  // A000000

//    return  ( a[k-1] >= a[k] );  // partitions (desc)
//    return  ( 2*a[k] <= 3*a[k-1] );  // A000000
}
// -------------------------

//  echo $(for n in $(seq 1 20); do ./bin $n 99; done | grep ct= ) | sed 's/ ct=/, /g;'


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n (n>=1)");

    ulong c = 5;
    NXARG(c, "Condition function:"
          "\n      0 ==> all words (condition always true),"
          "\n      1 ==> adjacent digits distinct"
          "\n      2 ==> up-down"
          "\n      3 ==> consecutive parts"
          "\n      4 ==> odd parts"
          "\n      5 ==> growth condition: a[k] <= 2*a[k-1]"
          "\n      6 ==> fall condition: 2*a[k] <= a[k-1]"
          "\n      7 ==> parts are Mersenne numbers"
          "\n      8 ==> parts are Mersenne numbers, partitions"
          "\n      9 ==> parts are powers of 2"
//          "\n      rest ==> see source"
          );


    composition_nz_restrpref P(n, cond_true);

    switch ( c )
    {
    case 0: P.first( cond_true );  break;
    case 1: P.first( cond_dist );  break;
    case 2: P.first( cond_updown );  break;
    case 3: P.first( cond_consec );  break;
    case 4: P.first( cond_odd );  break;
    case 5: P.first( cond_growth );  break;
    case 6: P.first( cond_fall );  break;
    case 7: P.first( cond_mers );  break;
    case 8: P.first( cond_mers_desc );  break;
    case 9: P.first( cond_2pow );  break;


    case 20: P.first( cond_change );  break;
    case 22: P.first( cond_2dist );  break;

    case 33: P.first( cond_no_3prog );  break;

    case 40: P.first( cond_par_diff );  break;

    case 45: P.first( cond_first_max );  break;
    case 46: P.first( cond_first_min );  break;
    case 47: P.first( cond_min );  break;

    case 50: P.first( cond_asc );  break;
    case 51: P.first( cond_desc );  break;

    case 55: P.first( cond_up_step );  break;

    case 60: P.first( cond_smooth );  break;
    case 61: P.first( cond_smooth_part );  break;

    case 70: P.first( cond_superdiag );  break;
    case 71: P.first( cond_subdiag );  break;

    case 88: P.first( cond_false );  break;

    case 99: P.first( cond_test );  break;

    default:  cout << "Not a valid condition!" << endl;
        return 1;
    }

    ulong ct = 0;

#ifdef TIMING
    P.first( );
    while ( P.valid() )  { ++ct;  P.next(); }

#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    while ( P.valid() )
    {
        ++ct;
#if 0
        cout << "[" << setw(2) << ct << "]";  // format for OEIS examples
#else
        ulong m = P.num_parts();
        cout << setw(4) << ct << ":";
        cout << "  [" << setw(2) << m << "]";
#endif

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( P.OK() );
        P.next();
    }

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 0
arg 1: 30 == n  [compositions of n (n>=1)]  default=9
[...]
 ct=536870912
./bin 30 0  6.92s user 0.00s system 99% cpu 6.927 total
 ==> 536870912/6.92 == 77,582,501 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-restrpref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-restrpref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

