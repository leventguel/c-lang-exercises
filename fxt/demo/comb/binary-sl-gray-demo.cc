
#include "comb/binary-sl-gray.h"

#include "bits/print-bin.h"
#include "ds/bitarray.h"

//#include "comb/composition-nz-rank.h"
//#include "comb/composition-nz-conj.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Binary numbers in a minimal-change order
//% related so subset-lex order ("SL-Gray" order).
//% Cf. OEIS sequence A217262.

// Cf. comb/mixedradix-sl-gray-demo.cc for the general case.
// Cf. bits/bit-sl-gray-demo.cc for generation in a binary word.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Number of digits (n>=1)");
//    jjassert( n>=1 );

    binary_sl_gray M(n);
#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
#else
    cout << endl;
#endif


    ulong ct = 0;
#ifdef TIMING
    if ( ! bq )
    {
        cout << "forward:" << endl;
        M.first();
    do  { ++ct; }  while ( M.next() );
    }
    else
    {
        cout << "backward:" << endl;
        M.last();
        do  { ++ct; }  while ( M.prev() );
    }

#else

    const ulong *x = M.data();
    bitarray B(1UL<<n);  B.clear_all();

//    ulong C[64];

//    M.last();
    do
    {
        cout << " " << setw(4) << ct << ":";
        M.print("    ", true );
        cout << "  ";

        print_bin("    ", 1UL << (n-1 - M.pos()), n);

        // position and direction of change:
        cout << "  " << M.pos();
        cout << "  " << (M.dir() > 0 ? '+' : '-');

        // internal data (track and direction):
        cout << "    " << M.tr_ << "  " << (M.dt_ == 1 ?  '+' : '-');


//        ulong r = 0;
//        for (ulong k=0; k<n; ++k)  if ( x[k] )  r |= (1UL << (n-1-k));
//        r ^= ~0UL;
//        print_bin("  ", r, n);
//        ulong nc = composition_nz_unrank(r, C, n+1);
//        print_vec("    ", C, nc);

        // Print set:
        print_deltaset_as_set("    ", M.data(), n, false );
//        print_multi_deltaset_as_set("    ", M.data(), n, false );

        cout << endl;

        ++ct;

        { ulong w = 0, m = 1;
            for (ulong j=0;  j<n;  ++j, m<<=1)  if ( x[j] )  w += m;
            jjassert( ! B.test_set( w ) );
        }
    }
    while ( M.next() );
//    while ( M.prev() );


    jjassert( B.all_set_q() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 0
forward:
 ct=1073741824
./bin 30 0  2.50s user 0.00s system 99% cpu 2.499 total
 ==> 1073741824/2.50 == 429,496,729 per second


 time ./bin 30 1
backward:
 ct=1073741824
./bin 30 1  2.80s user 0.00s system 99% cpu 2.806 total
 ==> 1073741824/2.80 == 383,479,222 per second

*/


/*

BENCHARGS=30 0
BENCHARGS=30 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/binary-sl-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/binary-sl-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

