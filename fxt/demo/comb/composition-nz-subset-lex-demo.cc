
#include "comb/composition-nz-subset-lex.h"

#include "comb/comb-print.h"
#include "comb/composition-print-aa.h"
#include "bits/print-bin.h"

//#include "comb/composition-nz-conj.h"
//#include "comb/composition-nz-rank.h"
#include "comb/is-unimodal.h"
#include "comb/is-smooth.h"
#include "sort/sort.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts, subset-lex order.

// Cf. comb/composition-nz-demo.cc for compositions into positive parts.
// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing list of parts
// Cf. comb/partition-desc-demo.cc for partitions as non-increasing list of parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");

    composition_nz_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
#ifdef COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS
    cout << "COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined." << endl;
#endif
    if ( !bq )
    {
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING


    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
//    ulong C[64];
    do
    {
#if 0
//        if ( P.last_part() != 1 )  continue;
//        if ( P.data()[0] != 1 )  continue;
        if ( ! is_smooth(P.data(), m, 1) )  continue;  // i-smooth A034297
//        if ( ! is_weakly_unimodal(P.data(), m) )  continue;  // with i-smoothness: A000000
        // with smoothness: A001522
//        if ( 0==(1UL & P.last_part()) )  continue;  // A001045
//        if ( ! is_sorted_desc(P.data(), m) )  continue;  // same as partition_desc
//        if ( ! is_sorted(P.data(), m) )  continue;  // same as partition_asc_subset_lex
#endif
#if 0
        bool q = 1;
        const ulong *x = P.data();
//        for (ulong j=1; j<m; ++j)  if ( x[j] >= x[j-1] )  { q=0; break; }  // partitions
//        for (ulong j=0; j<m; ++j)  if ( 0==(x[j] & 1) )  { q=0; break; }  // odd parts
//        for (ulong j=0; j<m; ++j)  if ( x[j] < 3 )  { q=0; break; }  // min/max part
        for (ulong j=0; j<m; ++j) // parts are Mersenne numbers: A104977 (absolute values)
        {
            ulong v = x[j];
            if ( 0!=(v&(v+1)) )  { q=0; break; }
        }
        if ( ! q )  continue;
#endif
#if 0
        bool q = 1;
        const ulong *x = P.data();
        for (ulong j=1; j<m; ++j)  // A003242: Carlitz compositions
            if ( x[j] == x[j-1] )  { q=0; break; }
        if ( ! q )  continue;
#endif

//        cout << P.last_part() << ",";  continue;  // A082850 (with backward order)
//        cout << m-1 << ",";  continue;  // A100661 (with backward order)

        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

        ulong r = composition_nz_rank(P.data(), m);
        r = ~r;
        r &= (1UL<<n) - 1;
        print_bin("  ", r, n-1);

        P.print("  ");

//        ulong nc = composition_nz_conj(P.data(), m, C);
//        print_vec("        ", C, nc);


        cout << endl;
        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( P.OK() );
#if 0
        ulong mx = P.unrank(ct);
        jjassert( P.OK() );
        jjassert( m == mx );
        jjassert( ct == P.rank() );
#endif
        ++ct;

    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
  ct=2147483648
./bin 32 0  4.18s user 0.00s system 99% cpu 4.185 total
 ==> 2147483648/4.18 == 513,752,068 per second

 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
  ct=2147483648
./bin 32 1  4.37s user 0.00s system 99% cpu 4.376 total
 ==> 2147483648/4.37 == 491,415,022 per second


With COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined:

 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
forward:
  ct=2147483648
./bin 32 0  4.17s user 0.00s system 99% cpu 4.170 total
 ==> 2147483648/4.17 == 514,984,088 per second

 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
backward:
  ct=2147483648
./bin 32 1  3.86s user 0.00s system 99% cpu 3.866 total
 ==> 2147483648/3.86 == 556,342,913 per second

*/

/*
BENCHARGS=32 0
BENCHARGS=32 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

