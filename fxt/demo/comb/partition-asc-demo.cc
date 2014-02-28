
#include "comb/partition-asc.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions as non-decreasing list of parts.
//% Same as: compositions into non-decreasing parts.
//% Cf. OEIS sequence A000041.
//% See also sequences A218829 and A218735.

// Cf. comb/partition-desc-demo.cc for partitions as non-increasing lists
// Cf. comb/partition-asc-subset-lex-demo.cc for partitions in subset-lex order
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts
// Cf. comb/mpartition-demo.cc for partitions into m parts
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. comb/composition-nz-demo.cc for all compositions as list of parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "integer partitions of n");

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    partition_asc P(n);

    ulong ct = 0;


#ifdef TIMING
#ifdef PARTITION_ASC_FIXARRAYS
    cout << "PARTITION_ASC_FIXARRAYS is defined" << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

//    ulong Z[64];
    ulong m = P.num_parts();
    do
    {
#if 0  // only into odd parts
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 0; j<m; ++j)
            if ( 0==(x[j] & 1) )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0  // only into distinct parts
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 1; j<m; ++j)
            if ( x[j]==x[j-1] )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0  // only into self-conjugate partitions
        if ( !partition_asc_is_self_conj( P.data(), m ) )  continue;
#endif

        ++ct;
        cout << setw(4) << ct << ": ";

//        { ulong j=m; do { --j; cout << " " << x[j]; } while (j); }  // non-increasing list
        cout << " [" << setw(2) << m << "] ";
//        cout << " d=" << setw(2) << P.durfee_n() << " ";

//        cout << " [" << setw(2) << n-m << "] ";  // A218829
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";  // A218735

        P.print("  ");

//        ulong pc = partition_asc_conj(P.data(), m, Z);
//        print_vec_rev("  ", Z, pc);

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

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

 time ./bin 110
arg 1: 110 == n  [integer partitions of n]  default=10
  ct=607163746
./bin 110  3.39s user 0.00s system 99% cpu 3.389 total
 ==> 607163746/3.39 == 179,104,349 per second


With PARTITION_ASC_FIXARRAYS:
 time ./bin 110
arg 1: 110 == n  [integer partitions of n]  default=10
PARTITION_ASC_FIXARRAYS is defined
  ct=607163746
./bin 110  2.88s user 0.00s system 99% cpu 2.877 total
 ==> 607163746/2.88 == 210,820,745 per second

*/

/*
BENCHARGS=110
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

