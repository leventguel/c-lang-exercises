
#include "comb/partition-asc-subset-lex.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions of n into positive parts, subset-lex order.
//% Loopless algorithm.

// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing list of parts
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions into positive parts in subset-lex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "partitions of n");

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    partition_asc_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_SUBSET_LEX_FIXARRAYS
    cout << "PARTITION_ASC_SUBSET_LEX_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0
        bool q = 1;
        for (ulong j=0; j<m; ++j)  // only odd parts
            if ( 0==(P.data()[j] & 1UL) )  { q=0;  break; }
        if ( !q )  continue;
#endif
#if 0
        bool qq = 1;
        for (ulong j=1; j<m; ++j)  // only distinct parts
            if ( P.data()[j-1] == P.data()[j]  )  { qq=0;  break; }
        if ( !qq )  continue;
#endif
#if 0  // only into powers of 2, cf. A018819
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 0; j<m; ++j)
        { ulong v=x[j];  if ( !!(v & (v-1)) )  { q=false; break; } }
        if ( !q )  continue;
#endif
#if 0  // only into self-conjugate partitions
        if ( !partition_asc_is_self_conj( P.data(), m ) )  continue;
#endif

        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

        P.print("  ");


        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

        ++ct;

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
arg 1: 110 == n  [partitions of n]  default=10
  ct=607163746
./bin 110  3.26s user 0.00s system 99% cpu 3.263 total
 ==> 607163746/3.26 == 186,246,547 per second

 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=10
PARTITION_ASC_SUBSET_LEX_FIXARRAYS defined.
  ct=607163746
./bin 110  2.72s user 0.00s system 99% cpu 2.723 total
 ==> 607163746/2.72 == 223,221,965 per second

*/

/*
BENCHARGS=110
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

