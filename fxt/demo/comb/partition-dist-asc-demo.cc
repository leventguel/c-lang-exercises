
#include "comb/partition-dist-asc.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions into distinct parts as non-decreasing list of parts,
//% lexicographic order.
//% Same as: compositions into distinct non-decreasing parts.
//% Cf. OEIS sequence A000009.

// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts
// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing compositions
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. seq/A179080-demo.cc for partitions into distinct parts and adjacent parts have different parity.
// Cf. comb/composition-nz-demo.cc for all compositions as lists of parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "integer partitions of n into distinct parts");

    partition_dist_asc P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0
        bool q = true;
        for (ulong j=1; j<m; ++j)  // min diff
            if ( P.data()[j] - P.data()[j-1] < 2 )
            { q=0;  break; }
        if ( ! q )  continue;
#endif
        ++ct;

        cout << setw(3) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");
        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 220
arg 1: 220 == n  [integer partitions of n into distinct parts]  default=16
  ct=1586861606
./bin 220  6.41s user 0.00s system 99% cpu 6.415 total
 ==> 1586861606/6.41 == 247,560,312 per second

*/

/*
BENCHARGS= 220
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

