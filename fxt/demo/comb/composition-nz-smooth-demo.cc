
#include "comb/composition-nz-smooth.h"

#include "comb/is-unimodal.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Left-smooth compositions in lexicographic order.
//% Same as "1-dimensional sand piles",
//% cf. OEIS sequence A186085.

// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "Smooth compositions of n");
    // works for n==0

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    composition_nz_smooth C(n);

    ulong ct = 0;

#ifdef TIMING
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    ulong m = C.num_parts();
    do
    {
#if 0  // OEIS sequence A001522: smooth weakly unimodal compositions
        // G.f.: sum(k>=1, -(-1)^k * x^(k*(k+1)/2) ) / prod(k>=1, 1 - x^k ).
        if ( ! is_weakly_unimodal(C.data(), m) )  continue;
        // strongly unimodal: ==1 for triangular numbers, else zero:
//        if ( ! is_strongly_unimodal(C.data(), m) )  continue;
#endif

        ++ct;
        cout << setw(4) << ct << ":  ";

        cout << "[" << setw(2) << m << "]" ;
//        cout << " [" << setw(2) << n-m << "]" ;  // A000000

        C.print("    ", true);

        cout << endl;

        if ( aa )  // ASCII art
        {
            C.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( C.OK() );
    }
    while ( (m=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct;  // A186085 1-dimensional sand piles with n grains.
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 43
arg 1: 43 == n  [Smooth compositions of n (n>=1)]  default=12
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=768425125
./bin 43  5.24s user 0.00s system 99% cpu 5.247 total
 ==> 768425125/5.24 == 146,646,016 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-smooth-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-smooth-demo.cc DEMOFLAGS=-DTIMING"
/// End:

