
#include "comb/catalan-path-lex.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Catalan paths in lexicographic order, CAT algorithm.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of paths is 2*n (n>=1)");
//    jjassert( n>=1 );

    bool pq = 0;
    NXARG(pq, "Whether do render paths (as ASCII art)");

    catalan_path_lex C(n);

    ulong ct = 0;
    ulong j = 0;

#ifdef TIMING
#ifndef CATALAN_PATH_LEX_NO_FLAT_STEPS
    cout << "FLAT STEPS allowed." << endl;
#endif
    do { ++ct; } while ( (j=C.next()) );
#else

    const ulong *x = C.data();
    const ulong n2 = 2 * n;

    do
    {
        ++ct;
        cout << setw(4) << ct << ":  ";
        C.print("    ", true );
        cout << "    " << setw(2) << j;

        cout << "    ";
        for (ulong i=1; i<=n2; ++i)
        {
            ulong d = x[i] - x[i-1] + 1;
            cout << " " << "-0+"[d];
//            cout << " " << ")x("[d];
//            cout << " " << "DhU"[d];
//            cout << " " << "\\-/"[d];
        }

        if ( pq )  // ASCII art
        {
            cout << endl;
            C.print_aa();
            cout << endl;
        }

        cout << endl;

        jjassert( C.OK() );
    }
    while ( (j=C.next()) );
#endif

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18
arg 1: 18 == n  [Length of paths is 2*n (n>=1)]  default=5
 ct=477638700
./bin 18  4.18s user 0.00s system 99% cpu 4.183 total
 ==> 477638700/4.18 == 114,267,631 per second


Following with CATALAN_PATH_LEX_NO_FLAT_STEPS *not* defined:
 time ./bin 18
arg 1: 18 == n  [Length of paths is 2*n (n>=1)]  default=4
FLAT STEPS allowed.
 ct=1767263190
./bin 18  11.26s user 0.00s system 99% cpu 11.268 total
 ==> 1767263190/11.26 == 156,950,549 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-path-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-path-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

