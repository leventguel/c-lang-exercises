
#include "comb/composition-nz-numparts.h"

#include "comb/comb-print.h"
#include "nextarg.h"

#include "aux0/sign.h"  // Abs()
#include "sort/convex.h"  // is_weakly_unimodal(), is_strongly_unimodal()

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"


//% OEIS sequence A187081: sand piles by height.
//% Same as: compositions of n where the first and the last parts are 1 and
//% the absolute difference between consecutive parts is <=1.
//% Also A186084: sand piles by base length.
//% Also A186085: sand piles with n grains.
//% Also A187080: fountains of coins by height.
//% Also A047998: fountains of coins by base length.
//% Also A005169: fountains of n coins.


// Cf. comb/composition-nz-weakly-unimodal-demo.cc for generation in lexicographic order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "Compositions of n (n>=1)");
    bool sq = 1;
    NXARG(sq, "Whether to generate sandpiles (else fountains of coins)");
    bool hq = 1;
    NXARG(hq, "Whether to gather stats about height (else about base length)");

    composition_nz_numparts P(n);
    P.first();

    ulong ct = 0;


    ulong * st = new ulong[n+1];  // statistics
    for (ulong j=0; j<=n; ++j)  st[j] = 0;

    const ulong *x = P.data();
    ulong k = P.num_parts();
    do
    {
#if 1
        // A187081: sand piles by height:
        if ( x[0]!=1 )  continue;

        bool q = true;
        if ( sq ) // sand piles
        {
            if ( x[k-1]!=1 )  continue;
            for (ulong j=1; j<k; ++j)
                if ( Abs<long>((long)(x[j]-x[j-1])) > 1 )
                { q=false; break; }
        }
        else  // fountains of coins
        {
            for (ulong j=1; j<k; ++j)
                if ( (long)(x[j]-x[j-1]) > 1 )
                { q=false; break; }
        }

        if ( !q )  continue;

        ulong h = 0;  // height or base length
        if ( hq )
        {
            for (ulong j=0; j<k; ++j)  // height = max value in x[]
                if ( h<x[j] )  h=x[j];
        }
        else  h = k;

        st[h] += 1;  // gather stats

        cout << " " << h << "  ";

#else
        // Other OEIS sequences:

        if ( ! is_strongly_unimodal(x, k) )  continue;  // A059618 strongly unimodal

//        if ( ! is_weakly_unimodal(x,k) )  continue;  // A001523 weakly unimodal

//        if ( ! is_weakly_unimodal(x,k) )  continue;  // and below
//        if ( is_strongly_unimodal(x, k) )  continue;  // A000000 weakly but not strictly unimodal

//        {  // odd parts only: Fibonacci numbers (A000045)
//            bool q = true;
//            for (ulong j=0; j<k; ++j)
//                if ( (x[j] & 1UL)==0 )
//                { q=false; break; }
//            if ( !q )  continue;
//        }


//        if ( test_strictly_convex(x, k) == 0 )  continue;  // A000000 strictly convex
        // 0, 0, 0, 1, 1, 3, 6, 10, 15, 24, 36, 53, 76, 105, 146, 200, 269, 360, 477, 624,
        //   814, 1053, 1353, 1730, 2200, 2781, 3502, 4391, 5479, 6814

//        if ( test_strictly_concave(x, k) == 0 )  continue;  // A000000 strictly concave
        // 0, 0, 0, 0, 1, 2, 3, 7, 11, 17, 25, 39, 55, 78, 108, 147, 201, 269, 355, 467


//        bool waq = is_weakly_concave(x, k);
//        if ( !waq )  continue;  // A000000 weakly concave
        // 1, 2, 4, 7, 13, 21, 36, 57, 91, 140, 217, 323, 485, 711, 1039, 1494, 2144, 3032,


//        { bool xq, aq;
//            xq =  (test_strictly_convex(x, k) == 0 );
//            aq =  (test_strictly_concave(x, k) == 0 );
//            if ( (xq) && (aq) )  continue;  // A000000 neither
//            // 0, 0, 0, 1, 2, 5, 9, 17, 26, 41, 61, 92, 131, 183, 254, 347, 470, 629, 832, 1091
//            // first three terms are wrong here...
//        }

//        bool wq = is_weakly_convex(x, k),  sq = (0!=test_strictly_convex(x, k));
//        bool wq = is_weakly_concave(x, k),  sq = (0!=test_strictly_concave(x, k));
//        cout << "  wq=" << wq << "  sq=" << sq << "  " << (sq && !wq) << endl;
//        jjassert( !(sq && !wq) );



//        {  bool q = true;
//            for (ulong j=0; j<k; ++j)  // compositions into parts <= b
//            {
////                if ( !(x[j]<=8) )  { q=false; break; }  // A079262(n+7)
//                if ( !(x[j]<=7) )  { q=false; break; }  // A066178(n)
////                if ( !(x[j]<=6) )  { q=false; break; }  // A001592(n+5)
////                if ( !(x[j]<=5) )  { q=false; break; }  // A001591(n+4)
////                if ( !(x[j]<=4) )  { q=false; break; }  // A000078(n+3)
////                if ( !(x[j]<=3) )  { q=false; break; }  // A000073(n+2)
////                if ( !(x[j]<=2) )  { q=false; break; }  // A000045(n+1)
//            }
//            if ( !q )  continue;
//        }

//        {  bool q = false;
//            for (ulong j=0; j<k; ++j)  // at least one part >=b
//            {
////                if ( x[j]>=1 )  { q=true; break; }  // A131577 0,1,2,4,8,...
////                if ( x[j]>=2 )  { q=true; break; }  // A000225 (shifted)
////                if ( x[j]>=3 )  { q=true; break; }  // A008466 (shifted) a(n) = 2^n-Fibonacci(n+2).
//                if ( x[j]>=4 )  { q=true; break; }  // A050231
////                if ( x[j]>=5 )  { q=true; break; }  // A050232
////                if ( x[j]>=6 )  { q=true; break; }  // A050233
////                if ( x[j]>=7 )  { q=true; break; }  // A143662
////                if ( x[j]>=8 )  { q=true; break; }  // A151975
//            }
//            if ( !q )  continue;
//        }


//        {  bool q = true;
//            for (ulong j=0; j<k; ++j)  // A189101
//            {
//                if ( x[j]==5 )  { q=false; break; }
//                if ( x[j]>7 )  { q=false; break; }
//            }
//            if ( !q )  continue;
//        }

#endif


        ++ct;

#ifndef TIMING
        cout << setw(4) << ct << ":";
        print_vec("    ", x, k, true);
//        cout << "  " << k;
        cout << endl;
#endif  // TIMING
    }
    while ( (k=P.next()) <= n );


    cout << "  stats:  ";
    for (ulong j=0; j<=n; ++j)  cout << st[j] << " ";
    cout << endl;
    delete [] st;

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*

Sand piles by height (A187081):
 for n in $(seq 1 15); do ./bin $n 1 1 | g '  stats' ; done | cut -d: -f2
    0 1
    0 1 0
    0 1 0 0
    0 1 1 0 0
    0 1 2 0 0 0
    0 1 4 0 0 0 0
    0 1 7 0 0 0 0 0
    0 1 12 0 0 0 0 0 0
    0 1 20 1 0 0 0 0 0 0
    0 1 33 2 0 0 0 0 0 0 0
    0 1 54 5 0 0 0 0 0 0 0 0
    0 1 88 11 0 0 0 0 0 0 0 0 0
    0 1 143 22 0 0 0 0 0 0 0 0 0 0
    0 1 232 44 0 0 0 0 0 0 0 0 0 0 0
    0 1 376 84 0 0 0 0 0 0 0 0 0 0 0 0
    0 1 609 158 1 0 0 0 0 0 0 0 0 0 0 0 0
    0 1 986 293 2 0 0 0 0 0 0 0 0 0 0 0 0 0
    0 1 1596 535 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    0 1 2583 969 12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    0 1 4180 1739 25 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Sand piles by base length (A186084):
 for n in $(seq 1 15); do ./bin $n 1 0 | g '  stats' ; done | cut -d: -f2
  0 1
  0 0 1
  0 0 0 1
  0 0 0 1 1
  0 0 0 0 2 1
  0 0 0 0 1 3 1
  0 0 0 0 0 3 4 1
  0 0 0 0 0 1 6 5 1
  0 0 0 0 0 1 4 10 6 1
  0 0 0 0 0 0 3 10 15 7 1
  0 0 0 0 0 0 2 8 20 21 8 1
  0 0 0 0 0 0 1 7 19 35 28 9 1
  0 0 0 0 0 0 0 5 18 40 56 36 10 1
  0 0 0 0 0 0 0 3 16 41 76 84 45 11 1
  0 0 0 0 0 0 0 1 12 41 86 133 120 55 12 1

Row sums: Sand piles with n grains: A186085
 echo $(for n in $(seq 1 15); do ./bin $n 1 1 | g 'ct=' ; done) | sed 's/ct=//g;s/ /, /g;'
1, 1, 1, 2, 3, 5, 8, 13, 22, 36, 60, 100, 166, 277, 461

Antidiagonal sums: A186505



Fountains of coins by height (A187080):
 for n in $(seq 1 15); do ./bin $n 0 1 | g '  stats' ; done | cut -d: -f2
  0 1
  0 1 0
  0 1 1 0
  0 1 2 0 0
  0 1 4 0 0 0
  0 1 7 1 0 0 0
  0 1 12 2 0 0 0 0
  0 1 20 5 0 0 0 0 0
  0 1 33 11 0 0 0 0 0 0
  0 1 54 22 1 0 0 0 0 0 0
  0 1 88 44 2 0 0 0 0 0 0 0
  0 1 143 85 5 0 0 0 0 0 0 0 0
  0 1 232 161 12 0 0 0 0 0 0 0 0 0
  0 1 376 302 25 0 0 0 0 0 0 0 0 0 0
  0 1 609 559 52 1 0 0 0 0 0 0 0 0 0 0


Fountains of coins by base length (A047998 ):
 for n in $(seq 1 15); do ./bin $n 0 0 | g '  stats' ; done | cut -d: -f2
  0 1
  0 0 1
  0 0 1 1
  0 0 0 2 1
  0 0 0 1 3 1
  0 0 0 1 3 4 1
  0 0 0 0 3 6 5 1
  0 0 0 0 2 7 10 6 1
  0 0 0 0 1 7 14 15 7 1
  0 0 0 0 1 5 17 25 21 8 1
  0 0 0 0 0 5 16 35 41 28 9 1
  0 0 0 0 0 3 16 40 65 63 36 10 1
  0 0 0 0 0 2 14 43 86 112 92 45 11 1
  0 0 0 0 0 1 11 44 102 167 182 129 55 12 1
  0 0 0 0 0 1 9 40 115 219 301 282 175 66 13 1


Row sums: A005169 fountains of n coins.
 echo $(for n in $(seq 1 15); do ./bin $n 0 0 | g 'ct=' ; done) | sed 's/ct=//g;s/ /, /g;'
1, 1, 2, 3, 5, 9, 15, 26, 45, 78, 135, 234, 406, 704, 1222


 */


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A187081-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A187081-demo.cc DEMOFLAGS=-DTIMING"
/// End:
