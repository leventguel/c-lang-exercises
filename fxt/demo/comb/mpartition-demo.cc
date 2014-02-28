
#include "comb/mpartition.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions of n into m parts.
//% Same as: compositions into m non-decreasing parts.
//% Cf. OEIS sequence A008284.

// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing compositions
// Cf. comb/partition-desc-demo.cc for partitions as non-increasing compositions

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "integer partitions of n");
    ulong m = 11;
    NXARG(m, "partitions into m parts");

    mpartition P(n, m);
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(3) << ct << ": ";
        const ulong *x = P.data();
        for (ulong k=0; k<m; ++k)  cout << " " << x[k];
        cout << endl;
#endif
    }
    while ( P.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 140 20
  ct=693703134
./bin 140 20  5.18s user 0.01s system 99% cpu 5.199 total
 ==> 693703134/5.18 == 133,919,523 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 140 20
  ct=693703134
./bin 140 20  3.81s user 0.00s system 99% cpu 3.817 total
 ==> 693703134/3.81 == 182,074,313 per second

*/

/*
BENCHARGS=140 20
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mpartition-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mpartition-demo.cc DEMOFLAGS=-DTIMING"
/// End:

