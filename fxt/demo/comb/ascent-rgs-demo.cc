
#include "comb/ascent-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Ascent sequences (restricted growth strings, RGS) in lexicographic order.
//% An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0, d(k)>=0,
//% and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the number
//% of ascents of its argument.
//% Cf. OEIS sequence A022493.

// Cf. seq/A218577-demo.cc for stats for ascent sequences
// Cf. comb/descent-rgs-demo.cc for descent RGS


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings");

    ascent_rgs A(n);

    ulong ct = 0;


#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "Whether to generate in backward order");
#ifdef ASCENT_RGS_FIXARRAYS
    cout << "ASCENT_RGS_FIXARRAYS defined." << endl;
#endif

    if ( bw )
    {
        cout << "backward:" << endl;
        A.last();
        do  { ++ct; }  while ( A.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        A.first();
        do  { ++ct; }  while ( A.next() );
    }
#else

    ulong j = n;
    do
    {
#if 0
        {  // limit max digit:
            const ulong *x = A.data();
            bool q = true;
            const ulong b = 2;
            // b = 1 ==> 2^n
            // b = 2 ==> (3^n + 1)/2
            // b = 3 ==> A000000
            // 1, 2, 5, 15, 52, 196, 767, 3045, 12150, 48562, 194201, 776747, 3106920, 12427600,
            // g.f.: (-3*x^3 + 6*x^2 - 5*x + 1)/(4*x^4 - 13*x^3 + 15*x^2 - 7*x + 1)
            for (ulong j=0; j<n; ++j)
                if ( x[j] > b )  { q=false;  break; }
            if ( ! q )  continue;
        }
#endif

        ++ct;


#if 1
        cout << setw(4) << ct << ":  ";

        // print RGS:
        print_vec("  ", A.data(), n, true );
//        print_vec("  ", A.m_, n, true );

        cout << setw(4) << j;

        cout << endl;
        jjassert( A.OK() );
#endif
    }
    while ( (j=A.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // OEIS sequence A022493
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 14 0
arg 1: 14 == n  [Length of strings]  default=5
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
forward:
 ct=796713190
./bin 14 0  2.97s user 0.00s system 99% cpu 2.969 total
 ==> 796713190/2.97 == 268,253,599 per second

 time ./bin 14 1
arg 1: 14 == n  [Length of strings]  default=5
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
backward:
 ct=796713190
./bin 14 1  3.07s user 0.00s system 99% cpu 3.073 total
 ==> 796713190/3.07 == 259,515,697 per second


 time ./bin 14 0
arg 1: 14 == n  [Length of strings]  default=5
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
ASCENT_RGS_FIXARRAYS defined.
forward:
 ct=796713190
./bin 14 0  3.15s user 0.00s system 99% cpu 3.155 total
 ==> 796713190/3.15 == 252,924,822 per second

 time ./bin 14 1
arg 1: 14 == n  [Length of strings]  default=5
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
ASCENT_RGS_FIXARRAYS defined.
backward:
 ct=796713190
./bin 14 1  3.15s user 0.00s system 99% cpu 3.154 total
 ==> 796713190/3.15 == 252,924,822 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ascent-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ascent-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

