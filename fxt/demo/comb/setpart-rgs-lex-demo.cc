
#include "comb/setpart-rgs-lex.h"

#include "comb/comb-print.h"


#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Set partitions as restricted growth strings (RGS).


//#define TIMING  // uncomment to disable printing

// Cf. comb/setpart-p-rgs-lex-demo.cc for the RGS for set partitions into p parts
// Cf. comb/setpart-ck-rgs-demo.cc for the Cooper-Kennedy RGS
// Cf. comb/setpart-zero-map-rgs-demo.cc for RGS using certain maps

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Partition set of n elements");
//    ulong px = 0;
//    NXARG(px, "If !=0, only list partitions into exactly px sets");
    bool bq = false;
    NXARG(bq, "whether to list backwards");

    setpart_rgs_lex P(n);
    if ( bq )  P.last();

    ulong ct = 0;

#ifdef TIMING
    if ( bq )  { do { ++ct; }  while ( P.prev() ); }
    else       { do { ++ct; }  while ( P.next() ); }

#else  // TIMING

    do
    {
#if 0 // limit max digit (max number of sets in partition)
        ulong m = 0;
        for (ulong k=0; k<n; ++k)
            if ( P.data()[k] > m )  m = P.data()[k];
//        if ( m>1 )  continue;  // 2^n (set partitions with at most 2 blocks)
//        if ( m>2 )  continue;  // A007051, A124302 (set partitions with at most 3 blocks)
        if ( m>3 )  continue;  // A007581, A124303 (set partitions with at most 4 blocks)
#endif

        ++ct;
        cout << setw(3) << ct << ":";
        P.print("  ", true);  // RGS
        print_vec("  ", P.m_, n);  // array of max in prefix
        P.print_sets("    ", 1);  // sets

        cout << endl;

        jjassert( P.OK() );
    }
    while ( bq ? P.prev() : P.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 15 0
 ct = 1382958545
./bin 15 0  8.79s user 0.03s system 99% cpu 8.822 total
 ==> 1382958545/8.79 == 157,333,167 per second

 time ./bin 15 1
 ct = 1382958545
./bin 15 1  7.28s user 0.01s system 100% cpu 7.286 total
 ==> 1382958545/7.28 == 189,966,833 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15 0
 ct = 1382958545
./bin 15 0  5.24s user 0.00s system 99% cpu 5.243 total
 ==> 1382958545/5.24 == 263,923,386 per second

 time ./bin 15 1
 ct = 1382958545
./bin 15 1  4.47s user 0.00s system 99% cpu 4.476 total
 ==> 1382958545/4.47 == 309,386,699 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

