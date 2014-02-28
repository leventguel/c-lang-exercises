
#include "comb/composition-ex-colex.h"

#include "comb/comb-print.h"
#include "nextarg.h"

#include "aux0/sign.h"  // Abs() (with OEIS counting)

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"


//% Compositions of n into exactly k parts in co-lexicographic (colex) order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Compositions of n (n>=1)");
    ulong k = 4;
    NXARG(k, "Into exactly k parts (must have: k<=n) ");
    bool rq = 0;
//    NXARG(rq, "Whether to reverse order");

    jjassert( k<=n );

    composition_ex_colex P(n, k);

    if ( rq )  P.last();
    else       P.first();

    ulong ct = 0;

#ifdef TIMING
    if ( rq )  do { ++ct; }  while  ( P.prev() != k );
    else       do { ++ct; }  while  ( P.next() != k );

#else
    const ulong *x = P.data();
    ulong q = k-1;
    do
    {
        // OEIS sequences:
//        {  bool qq = true;
//            if ( x[0]!=1 || x[k-1]!=1 )  qq = false;
//            else
//            {
//                for (ulong j=1; j<k; ++j)
//                    if ( Abs<long>((long)(x[j]-x[j-1])) > 1 )
//                    { qq=false; break; }
//            }
//            if ( !qq )  goto skip;  // A186085 (sand piles), triangle by base-len is A186084
//        }
//        {  bool qq = true;
//            for (ulong j=1; j<k; ++j)
//                if ( Abs((long)(x[j]-x[j-1])) != 1 )
//                { qq=false; break; }
//            if ( !qq )  goto skip;  // A000000 (not in OEIS)
//        }
//        {  bool qq = true;
//            for (ulong j=1; j<k; ++j)  if ( x[j]-x[j-1] != 1 )  { qq=false; break; }
//            if ( !qq )  goto skip;  // A129372
//        }
//        {  bool qq = true;
//            for (ulong j=1; j<k; ++j)  if ( x[j]==x[j-1] )  { qq=false; break; }
//            if ( !qq )  goto skip;  // A106351
//        }
//        {  if (k>1 ) { bool qq = false;
//            for (ulong j=1; j<k; ++j)  if ( x[j]==x[j-1] )  { qq=true; break; }
//            if ( !qq )  goto skip; }  // A131044
//        }
//        {  bool qq = true;
//            for (ulong j=0; j<k; ++j)  if ( x[j]%2 )  { qq=false; break; }
//            if ( !qq )  goto skip;  // blown up Pascal triangle
//        }
//        {  bool qq = true;
//            for (ulong j=1; j<k; ++j)  if ( ((x[j]^x[j-1])&1) !=0 )  { qq=false; break; }
//            if ( !qq )  goto skip;  // (also try ==0), neither in OEIS
//        }
//        {  bool qq = true;
//            for (ulong j=0; j<k; ++j)
//                for (ulong i=j+1; i<k; ++i)
//                    if ( x[j]==x[i] )  { qq=false; goto dort; }
//        dort:
//            if ( !qq )  goto skip;  // A072574, cf. A032020
//        }
//        {  bool qq = false;
//            for (ulong j=0; j<k; ++j)
//                for (ulong i=j+1; i<k; ++i)
//                    if ( x[j]==x[i] )  { qq=true; goto dort; }
//        dort:
//            if ( !qq )  goto skip;  // A000000 (not in OEIS)
//        }

//        { if ( x[0] == 1 )  goto skip;  // A005773
//            for (ulong j=0; j<k; ++j)
//                if ( x[j] > 3 )  goto skip;
//        }

        ++ct;
        cout << setw(4) << ct << ":";
        P.print("    ");
        cout << "  " << q << "  ";

        // show corresponding compositions of n-k into at most k parts:
        cout << "    [";
        for (ulong j=0; j<k; ++j)
        {
            cout << " ";
            ulong v = x[j] - 1;
            if ( 0==v )  cout << '.';
            else         cout << v;
        }
        cout << " ]";
        cout << endl;

        goto skip;  // avoid warning without OEIS counting
    skip:
        if ( rq )  q = P.prev();
        else       q = P.next();
    }
    while ( q != k );
#endif

//    print_vec("    ", x, k+1, true);
//    cout << "  test:" << P.nk1_ << endl;

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

----------- next():

 time ./bin 40 10
  ct=211915132
./bin 40 10  1.05s user 0.01s system 99% cpu 1.064 total
 ==> 211915132/1.05 == 201,823,935 per second

----------- prev():  (set variable rq=1) identical

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

----------- next():
 time ./bin 40 10
arg 1: 40 == n  [Compositions of n (n>=1)]  default=8
arg 2: 10 == k  [Into exactly k parts (must have: k>=n) ]  default=4
  ct=211915132
./bin 40 10  0.61s user 0.00s system 99% cpu 0.610 total
 ==> 211915132/0.61 == 347,401,855 per second

----------- prev():
./bin 40 10  0.67s user 0.00s system 99% cpu 0.676 total
 ==> 211915132/0.67 == 316,291,241 per second
*/



/*
Triangle:
  for n in $(seq 1 60); do echo $(for k in $(seq 1 $n); do ./bin $n $k | grep ct= | sed 's/ct=//g'; done;); done

1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
1 6 15 20 15 6 1
1 7 21 35 35 21 7 1
1 8 28 56 70 56 28 8 1
1 9 36 84 126 126 84 36 9 1

Row sums:
  for n in $(seq 1 60); do echo 0 $(for k in $(seq 1 $n); do ./bin $n $k | grep ct= | sed 's/  ct=/+/g'; done;); done | bc

 */


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-ex-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-ex-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
