
#include "comb/descent-rgs.h"

#include "comb/comb-print.h"

//#include "comb/is-ascent-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Descent sequences (restricted growth strings, RGS), lexicographic order.
//% A descent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//%   d(k)>=0, and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.)
//%   counts the number of descents of its argument.
//% The number of length-n RGS is (OEIS sequence A225588)
//%   1, 1, 2, 4, 9, 23, 67, 222, 832, 3501, 16412, 85062, 484013, ...

// Cf. seq/A225624-demo.cc for stats for descents RGS
// Cf. comb/ascent-rgs-demo.cc for ascent RGS

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of strings");

    descent_rgs A(n);

    ulong ct = 0;


#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "Whether to generate in backward order");
#ifdef DESCENT_RGS_FIXARRAYS
    cout << "DESCENT_RGS_FIXARRAYS defined." << endl;
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
            const ulong b = 3;
            // b = 1 ==> 2^(n-1)
            // b = 2 ==> A164039: a(n+1) = 3*a(n) - n
            // b = 3 ==> A000000
            for (ulong j=0; j<n; ++j)
                if ( x[j] > b )  { q=false;  break; }
            if ( ! q )  continue;
        }
#endif

//        if ( ! is_ascent_rgs( A.data(), n) )  continue;
        // deviates from n==7 on: ct=221

        ++ct;


#if 1
        cout << setw(4) << ct << ":  ";

        // print RGS:
        print_vec("  ", A.data(), n, true );
        print_vec("  ", A.m_, n, true );

        cout << setw(4) << j;

        cout << endl;
//        jjassert( A.OK() );
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


 time ./bin 16 0
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
forward:
 ct=1146389206
./bin 16 0  4.17s user 0.00s system 99% cpu 4.171 total
 ==> 1146389206/4.17 == 274,913,478 per second

 time ./bin 16 1
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
backward:
 ct=1146389206
./bin 16 1  4.98s user 0.00s system 99% cpu 4.982 total
 ==> 1146389206/4.98 == 230,198,635 per second


 time ./bin 16 0
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
DESCENT_RGS_FIXARRAYS defined.
forward:
 ct=1146389206
./bin 16 0  4.04s user 0.00s system 99% cpu 4.039 total
 ==> 1146389206/4.04 == 283,759,704 per second

 time ./bin 16 1
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
DESCENT_RGS_FIXARRAYS defined.
backward:
 ct=1146389206
./bin 16 1  4.93s user 0.00s system 99% cpu 4.933 total
 ==> 1146389206/4.93 == 232,533,307 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/descent-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/descent-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

