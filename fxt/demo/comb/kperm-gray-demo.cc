
#include "comb/kperm-gray.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "comb/check-kpermgen.h"

#include "aux0/factorial.h"  // for timing

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Generate all k-permutations of n elements in minimal-change order
//%   via Gray code for falling factorial numbers, CAT algorithm.
//% Same as: k-prefixes of permutations of n elements.
//% Same as: arrangements of k out of n elements.

// Cf. comb/kperm-lex-demo.cc for lexicographic order
// Cf. comb/arrangement-rgs-demo.cc for all arrangements

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Total of n elements.");

    ulong k = 3;
    NXARG(k, "Permutations of k elements (1<=k<=n).");
    if ( k<1 )  k = 1;
    if ( k>n )  k = n;

    kperm_gray P(n);
    P.first(k);


#ifdef TIMING
    while ( P.next() ) { ; }
    cout << " ct=" << ffactpow(n,k) << endl;

#else

    bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *ix = P.invdata();
    const ulong *a = P.d_;

    check_kpermgen C(n, k);
    C.first(P.data());

    ulong ct = 0;
    ulong sw1, sw2;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        print_perm("    ", x, k, dfz);
        print_perm("", x+k, n-k, dfz);

        P.get_swap(sw1, sw2);
        cout << "  (" << sw1 << ", " << sw2 << ")";

        print_mixedradix("    ", a, n-1, dfz);

        print_perm("    ", ix, n, dfz);

        cout << endl;

        jjassert( ! C.is_repeat() );
    }
    while ( P.next() );

    jjassert( C.have_all() );

#endif  // TIMING

    return 0;
}
// -------------------------


/*
Timing:
%  time ./bin 12 12
arg 1: 12 == n  [Total of n elements.]  default=5
arg 2: 12 == k  [Permutations of k elements (1<=k<=n).]  default=3
./bin 12 12  3.01s user 0.00s system 100% cpu 3.011 total
 ==> 12!/3.01 == 159,136,744 per second


%  time ./bin 12 11
arg 1: 12 == n  [Total of n elements.]  default=5
arg 2: 11 == k  [Permutations of k elements (1<=k<=n).]  default=3
./bin 12 11  3.01s user 0.00s system 99% cpu 3.010 total
 ==> 12!/3.01 == 159,136,744 per second

% time ./bin 12 10
arg 1: 12 == n  [Total of n elements.]  default=5
arg 2: 10 == k  [Permutations of k elements (1<=k<=n).]  default=3
./bin 12 10  1.51s user 0.00s system 99% cpu 1.510 total
 ==> 239500800/1.51 == 158,609,801 per second

% time ./bin 24 6
arg 1: 24 == n  [Total of n elements.]  default=5
arg 2: 6 == k  [Permutations of k elements (1<=k<=n).]  default=3
./bin 24 6  0.54s user 0.00s system 99% cpu 0.544 total
 ==> 96909120/0.54 == 179,461,333 per second

% time ./bin 52 5
arg 1: 52 == n  [Total of n elements.]  default=5
arg 2: 5 == k  [Permutations of k elements (1<=k<=n).]  default=3
./bin 52 5  1.69s user 0.00s system 99% cpu 1.692 total
 ==> 311875200/1.69 == 184,541,538 per second

% time ./bin 100 4
arg 1: 100 == n  [Total of n elements.]  default=5
arg 2: 4 == k  [Permutations of k elements (1<=k<=n).]  default=3
./bin 100 4  0.50s user 0.00s system 98% cpu 0.502 total
 ==> 94109400/0.50 == 188,218,800 per second


BENCHARGS=12 12
BENCHARGS=12 11
BENCHARGS=12 10
BENCHARGS=24 6
BENCHARGS=52 5
BENCHARGS=100 4

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/kperm-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/kperm-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

