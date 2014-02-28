
#include "comb/partition-dist-desc.h"

//#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions into distinct parts as decreasing list of parts.
//% Same as: compositions into distinct decreasing parts.
//% Lexicographic order.
//% Cf. OEIS sequence A000009.

// Cf. comb/partition-desc-demo.cc for partitions as non-increasing lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "integer partitions of n");

    partition_dist_desc P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0
        bool q = 1;
        for (ulong j=0; j<m; ++j)  // odd parts only
            if ( 0==(P.data()[j] & 1 ) )  { q=0; break; }
        if ( ! q )  continue;
#endif
#if 0  // A001399, A069905, A211540:
        if ( P.num_parts() != 3 )  continue;
#endif
       ++ct;
        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

//        cout << "  [" << setw(2) << n-m << "]";
//        cout << "  [" << setw(2) << P.data()[m-1] << "]";
//        cout << "  [" << setw(2) << P.s_ << "]";

        P.print("  ");

        cout << endl;

        jjassert( P.OK() );
//        jjassert( ct < 66 );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 200
arg 1: 200 == n  [integer partitions of n]  default=19
 ct=487067746
./bin 200  4.71s user 0.00s system 99% cpu 4.710 total
 ==> 487067746/4.71 == 103,411,411 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

