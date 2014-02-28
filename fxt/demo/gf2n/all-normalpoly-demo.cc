
#include "bpol/all-irredpoly.h"
// demo-include "bits/bit-necklace.h"
// demo-include "bpol/necklace2bitpol.h"
#include "bpol/normalbasis.h"
// demo-include "bpol/bitpol-normal.cc"
#include "bmat/bitmat-funcs.h"

#include "bpol/bitpol-print.h"

#include "bpol/gf2n-trace.h"
#include "bits/print-bin.h"

#include "fxttypes.h"  // ulong
#include "nextarg.h"  // NXARG()

#include "fxtio.h"
#include "jjassert.h"
#include "fxtalloca.h"


//% Find all normal binary polynomials of degree n.
//% Print all corresponding multiplier matrices.
//% Cf. OEIS sequences A027362 and A107222.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Degree of the polynomials");
    ulong pp = 3;
    NXARG(pp, "How to print polynomials:\n"
          "    1==>binary, 2==>as poly., 3==> both, 0==>just count");
    ulong mq = 0;
    NXARG(mq, "Whether to print multiplication matrix");

    ALLOCA(ulong, M, n);  // multiplier matrix
    for (ulong j=0; j<n; ++j)  M[j] = 0;
    all_irredpoly ip(n);
    ulong *Mp = M;

    ulong nct = 0;  // count normal polynomials
    ulong pct = 0;  // count primitive normal polynomials
    ulong p = ip.data();

    do
    {
        const bool nq = bitpol_normal_q(p, n, 1, Mp);
//        const bool nq = true;  // for timing
//        jjassert( nq == bitpol_normal2_q(p, n) );

//        print_bin("neckl:  ", ip.bn_.a_, n );
//        if ( !nq )  cout << endl;

        if ( nq )
        {
            ++nct;
            ulong pq = ip.is_primitive();  // computes just a gcd
//            ulong pq = 1;  // for timing
            if ( pq )  ++pct;

#ifndef TIMING

            if ( 0==pp )  goto next;  // just count

            cout << setw(3) << nct << ":";
            if ( pp )
            {
                cout << " c =";
                if ( pp&1 )  bitpol_print_bin("  ", p);
                if ( pq )  cout << "  P";  // primitive polynomial
                else       cout << "   ";
                if ( pp==3 )  cout << " == ";
                if ( pp&2 )  bitpol_print("  ", p, n+1);
            }

            cout << endl;

            if ( mq )
            {
                bitmat_print("M=", M, n);
                cout << endl;
            }
#endif  // TIMING
            goto next;  // avoid compiler warning with TIMING defined
        }

    next:
        p = ip.next();
    }
    while ( p );

    cout << "  n=" << n;
    cout << "   #= " << nct << "   #primitive = " << pct;
    cout << "   #non-primitive = " << nct-pct;
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing:

  n=24   #= 262144   #primitive = 103680   #non-primitive = 158464
./bin 24  27.92s user 0.14s system 99% cpu 28.060 total
 ==> 2^24/27.92 == 600,903 per second

  n=23   #= 182183   #primitive = 178259   #non-primitive = 3924
./bin 23  13.27s user 0.07s system 99% cpu 13.344 total
 ==> 2^23/13.27 == 632,148 per second

  n=22   #= 95232   #primitive = 59986   #non-primitive = 35246
./bin 22  6.19s user 0.05s system 99% cpu 6.241 total
 ==> 2^22/6.19 == 677,593 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 24
./bin 24  5.66s user 0.00s system 99% cpu 5.662 total
 ==> 2^24/5.66 == 2,964,172 per second

 Omitting test for normality:
./bin 24  2.03s user 0.00s system 99% cpu 2.027 total
 ==> 2^24/2.03 == 8,264,638 per second

 Omitting test for primitivity:
./bin 24  5.62s user 0.00s system 99% cpu 5.619 total
 ==> 2^24/5.62 == 2,985,269 per second

 Omitting test for normality and primitivity:
./bin 24  1.93s user 0.00s system 99% cpu 1.930 total
 ==> 2^24/1.93 == 8,692,858 per second

*/


/*
for f in $(seq 2 30) ; do ./bin $f 0; done \
  | grep --line-buffered \#  | sed -u s/non-primitive/N/ | sed -u s/primitive/P/

    n=2   #= 1   #P = 1   #N = 0
    n=3   #= 1   #P = 1   #N = 0
    n=4   #= 2   #P = 1   #N = 1
    n=5   #= 3   #P = 3   #N = 0
    n=6   #= 4   #P = 3   #N = 1
    n=7   #= 7   #P = 7   #N = 0
    n=8   #= 16   #P = 7   #N = 9
    n=9   #= 21   #P = 19   #N = 2
    n=10   #= 48   #P = 29   #N = 19
    n=11   #= 93   #P = 87   #N = 6
    n=12   #= 128   #P = 52   #N = 76
    n=13   #= 315   #P = 315   #N = 0
    n=14   #= 448   #P = 291   #N = 157
    n=15   #= 675   #P = 562   #N = 113
    n=16   #= 2048   #P = 1017   #N = 1031
    n=17   #= 3825   #P = 3825   #N = 0
    n=18   #= 5376   #P = 2870   #N = 2506
    n=19   #= 13797   #P = 13797   #N = 0
    n=20   #= 24576   #P = 11255   #N = 13321
    n=21   #= 27783   #P = 23579   #N = 4204
    n=22   #= 95232   #P = 59986   #N = 35246
    n=23   #= 182183   #P = 178259   #N = 3924
    n=24   #= 262144   #P = 103680   #N = 158464
    n=25   #= 629145   #P = 607522   #N = 21623
    n=26   #= 1290240   #P = 859849   #N = 430391
    n=27   #= 1835001   #P = 1551227   #N = 283774
    n=28   #= 3670016   #P = 1815045   #N = 1854971
    n=29   #= 9256395   #P = 9203747   #N = 52648
    n=30   #= 11059200   #P = 5505966   #N = 5553234

  n=31   #= 28629151   #P = 28629151   #N = 0
  n=32   #= 67108864   #P = 33552327   #N = 33556537
  n=33   #= 97327197   #P = 78899078   #N = 18428119

OEIS seqs.:  A027362,      A107222,     A000000

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/all-normalpoly-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/all-normalpoly-demo.cc DEMOFLAGS=-DTIMING"
/// End:
