
#include "comb/composition-nz-left-smooth.h"

#include "comb/is-unimodal.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Left-smooth compositions in lexicographic order.
//% Cf. OEIS sequence A005169.

// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Left-smooth compositions of n");
    // jjassert( n>=1 );  // composition of n=0 as one part ==0

    ulong aa = 0;
    NXARG(aa, "If aa!=0, render as compositions (1) or fountains of coins (2)");

    composition_nz_left_smooth C(n);

    ulong ct = 0;

#ifdef TIMING
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    ulong m = C.num_parts();
    do
    {
#if 0
        // OEIS sequence A053260: Coefficients of the '5th order' mock theta function psi_0(q)
        // Partitions of n such that each part occurs at most twice,
        //   the largest part is unique and if k occurs as a part then
        //   all smaller positive integers occur.
        // G.f.: psi_0(q) = sum(n>=0, q^((n+1)*(n+2)/2) * prod(k=1..n, 1 + q^k ) )
//        if ( ! is_strongly_unimodal(C.data(), m) )  continue;

        // OEIS sequence A001524: stacks with strictly receding left wall.
        // G.f.: 1 + sum(n>=1, z^(n*(n+1)/2) / ( (1-z^n) * prod(i=1..n-1, (1-z^i) )^2)
        if ( ! is_weakly_unimodal(C.data(), m) )  continue;
#endif

        ++ct;
        cout << setw(4) << ct << ":  ";

        cout << "[" << setw(2) << m << "]" ;
//        cout << " [" << setw(2) << n-m << "]" ;  // A000000


        C.print("    ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            if ( aa==1 )  C.print_composition_aa();
            else          C.print_fountain_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( C.OK() );
    }
    while ( (m=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct;  // A005169 fountains of n coins.
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 42
arg 1: 42 == n  [Left-smooth compositions of n]  default=9
arg 2: 0 == aa  [Whether to render as compositions (1) or fountains of coins (2)]  default=0
 ct=3566196321
./bin 42  12.60s user 0.00s system 99% cpu 12.608 total
 ==> 3566196321/12.60 == 283,031,454 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-left-smooth-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-left-smooth-demo.cc DEMOFLAGS=-DTIMING"
/// End:

