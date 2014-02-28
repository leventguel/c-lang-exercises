
#include "comb/partition-asc-sorts2-pp.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "aux1/copy.h"  // fill()
#include "fxtalloca.h"

#include "fxttypes.h"
#include "nextarg.h"

#include "jjassert.h"

//% Partitions into parts of s[k] sorts for part (size) k.
//% Representation as non-decreasing lists.
//% Lexicographic order: major order by parts, minor by sorts.
//% Cf. OEIS sequence A000219 (planar partitions).
//% Cf. OEIS sequences (partitions of n into parts of s kinds):
//% A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
//% A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).

// Cf. comb/partition-asc-sorts2-demo.cc
// Cf. comb/composition-nz-sorts2-pp-demo.cc


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "partitions of n");

    ulong ns = 0;
    NXARG(ns, "Number of sorts for parts by size (0==>1,2,3,4,...,n)");

    ulong ct = 0;

#ifdef TIMING
    partition_asc_sorts2_pp P(n, ns);
#ifdef PARTITION_ASC_SORTS2_PP_FIXARRAYS
    cout << "PARTITION_ASC_SORTS2_PP_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ALLOCA(ulong, vns, n);
    fill(vns, n, ns);
    RESTARGS("Optionally supply radix for all part sizes (ns ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  vns[k-3] = strtoul(argv[k], 0, 10);

    partition_asc_sorts2_pp P(n, ns, (argc>3? vns:0) );

    ulong m = P.num_parts();
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";
        P.print("  ");
//        P.print_by_sorts("  ");
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


 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=607163746
./bin 110 1  4.51s user 0.00s system 99% cpu 4.509 total
 ==> 607163746/4.51 == 134,626,107 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=962759294
./bin 60 2  4.92s user 0.00s system 99% cpu 4.926 total
 ==> 976562500/4.92 == 198,488,313 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=1837560960
./bin 35 4  7.04s user 0.00s system 99% cpu 7.048 total
 ==> 1837560960/7.04 == 261,017,181 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=4053978040
./bin 22 8  12.06s user 0.00s system 99% cpu 12.065 total
 ==> 4053978040/12.06 == 336,150,749 per second



 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=607163746
./bin 110 1  4.31s user 0.00s system 99% cpu 4.314 total
 ==> 607163746/4.31 == 140,873,258 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=962759294
./bin 60 2  4.39s user 0.00s system 99% cpu 4.392 total
 ==> 976562500/4.39 == 222,451,594 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=1837560960
./bin 35 4  6.45s user 0.00s system 99% cpu 6.455 total
 ==> 1837560960/6.45 == 284,893,172 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=4053978040
./bin 22 8  11.86s user 0.00s system 99% cpu 11.859 total
 ==> 4053978040/11.86 == 341,819,396 per second

*/

/*
BENCHARGS=110 1
BENCHARGS=60 2
BENCHARGS=35 4
BENCHARGS=22 8
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-sorts2-pp-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-sorts2-pp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

