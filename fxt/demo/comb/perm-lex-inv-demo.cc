
#include "comb/perm-lex-inv.h"


#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

#include "perm/permq.h"  // is_inverse()

#include "jjassert.h"

//% Generate all permutations in lexicographic order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_lex_inv P(n);

#ifdef TIMING
#ifdef PERM_LEX_INV_FIXARRAYS
    cout << "PERM_LEX_INV_FIXARRAYS is defined." << endl;
#endif
#ifdef PERM_LEX_INV_OPT
    cout << "PERM_LEX_INV_OPT is defined." << endl;
#endif

    ulong ct = 0;
    do { ++ct; }  while ( P.next() );

    // make sure program updates inverse permutations:
//    jjassert( is_inverse(P.data(), P.invdata(), n) );
    cout << "ct=" << ct << endl;

#else

    bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *xi = P.invdata();

    cout << "         permutation         inv. perm.";
    cout << endl;

    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);
        P.print_inv("    ", dfz);
        if ( ! is_inverse(x, xi, n) )  cout << " !";

        cout << endl;
        jjassert( is_inverse(x, xi, n) );
    }
    while ( P.next() );

#endif

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
PERM_LEX_INV_FIXARRAYS is defined.
PERM_LEX_INV_OPT is defined.
ct=479001600
./bin 12  2.26s user 0.00s system 99% cpu 2.258 total
 ==> 479001600/2.26 == 211,947,610 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-lex-inv-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-lex-inv-demo.cc DEMOFLAGS=-DTIMING"
/// End:

