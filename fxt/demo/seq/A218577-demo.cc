
#include "comb/ascent-rgs.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% OEIS sequence A218577:
//% triangle, length-n ascent sequences with maximal element k-1.
//% An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0, d(k)>=0,
//% and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the number
//% of ascents of its argument.
//% Also A137251: triangle, sequences with k ascents.
//% Also A175579: triangle, sequences with k-1 zeros.
//% Also A218579: triangle, sequences with position of last zero at index k-1.
//% Also A218580: triangle, sequences with position of first occurrence of maximal value at index k-1.
//% Also A218581: triangle, sequences with position of last occurrence of maximal value at index k-1.


// Cf. seq/A225624-demo.cc for stats for descent sequences
// Cf. comb/ascent-rgs-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings, n>=1");
    jjassert( n>=1 );  // else word_stats will not work
    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "    0 ==> max element\n"
          "    1 ==> number of ascents\n"
          "    2 ==> number of descents\n"
          "    3 ==> number of zeros - 1\n"  // same stats as 5
          "    4 ==> number of maximal digits - 1\n"
          "    5 ==> number of fixed points - 1\n"  // same stats as 3
          "    6 ==> position of last occurrence of zero\n"
          "    7 ==> position of first occurrence of the maximal value\n"
          "    8 ==> position of last occurrence of the maximal value\n"
          "    9 ==> number of flat steps\n"
          "   10 ==> number of odd values\n"
//          "   11 ==> number of \n"
          );

    ascent_rgs A(n);
    word_stats W(A.data(), n);

    ulong ct = 0;
    ulong * st = new ulong[n];  // stats
    for (ulong k=0; k<n; ++k)  st[k] = 0;

#ifndef TIMING
    const ulong *x = A.data();
#endif

    ulong j = 0;
    do
    {
#if 0
        {  // limit max digit:
            bool q = true;
            const ulong b = 2;
            // b = 1 ==> 2^n
            // b = 2 ==> (3^n + 1)/2
            // b = 3 ==> A000000
            // 1, 2, 5, 15, 52, 196, 767, 3045, 12150, 48562, 194201, 776747, 3106920, 12427600,
            // g.f.: (-3*x^3 + 6*x^2 - 5*x + 1)/(4*x^4 - 13*x^3 + 15*x^2 - 7*x + 1)
            for (ulong k=0; k<n; ++k)
                if ( x[k] > b )
                { q=false;  break; }
            if ( ! q )  continue;
        }
#endif


        ++ct;
        ulong s = 0;
        switch ( sq )
        {
        case 0:  // by max element: A218577
            s = W.max_val();
            break;


        case 1:  // by number of ascents: A137251
            s = A.num_ascents();  // simplified: s==A.m[n-1]
//            jjassert( s == W.num_ascents() );
            break;

        case 2:  // by number of descents: A000000
            s = W.num_descents();
            // 1,
            // 2, 0,
            // 4, 1, 0,
            // 8, 7, 0, 0,
            // 16, 33, 4, 0, 0,
            // 32, 131, 53, 1, 0, 0,
            // 64, 473, 429, 48, 0, 0, 0,
            // 128, 1611, 2748, 822, 26, 0, 0, 0,
            // 256, 5281, 15342, 9305, 1048, 8, 0, 0, 0,
            // 512, 16867, 78339, 83590, 21362, 937, 1, 0, 0, 0,
            // 1024, 52905, 376159, 647891, 307660, 35841, 594, 0, 0, 0, 0,
            // 2048, 163835, 1728458, 4537169, 3574869, 834115, 45747, 262, 0, 0, 0, 0,
            // 4096, 502769, 7689744, 29532566, 35900857, 14475124, 1752513, 45355, 76, 0, 0, 0, 0,
            // 8192, 1532883, 33393393, 182034751, 324623778, 206587438, 45552389, 2945144, 35209, 13, 0, 0, 0, 0,
            break;


        case 3:  // by number of zeros: A175579
            s = W.num_zeros() - 1;  // note: -1
//            jjassert( s == W.num_min_val() - 1 );
            break;


        case 4:  // by number of max digits: A000000
            s = W.num_max_val() - 1;  // note: -1
            // 1,
            // 1, 1,
            // 3, 1, 1,
            // 9, 4, 1, 1,
            // 32, 14, 5, 1, 1,
            // 134, 55, 20, 6, 1, 1,
            // 643, 249, 86, 27, 7, 1, 1,
            // 3471, 1274, 419, 126, 35, 8, 1, 1,
            // 20809, 7262, 2281, 657, 176, 44, 9, 1, 1,
            // 137147, 45683, 13704, 3794, 977, 237, 54, 10, 1, 1,
            // 985536, 314563, 90251, 23977, 5965, 1394, 310, 65, 11, 1, 1,
            // 7669233, 2353714, 647597, 165008, 39571, 8969, 1924, 396, 77, 12, 1, 1,
            break;

        case 5:  // by number of fixed points (same as number of zeros): A175579
            s = W.num_fixed_points() - 1;  // note: -1
            break;


        case 6:  // position of last zero: A218579
            s = W.last_zero_idx();
//            jjassert( s == W.last_min_idx() );
            break;

        case 7:  // position of first occurrence of max: A218580
            s = W.first_max_idx();
            break;

        case 8:  // position of last occurrence of max: A218581
            s = W.last_max_idx();
            break;

        case 9:  // number of flat steps: A000000
            s = W.num_flat_steps();
            // Leftmost colum: A138265 (upper triangular zero-one matrices with n ones and no zero rows or columns)
            // 1,
            // 1, 1,
            // 2, 2, 1,
            // 5, 6, 3, 1,
            // 16, 20, 12, 4, 1,
            // 61, 80, 50, 20, 5, 1,
            // 271, 366, 240, 100, 30, 6, 1,
            // 1372, 1897, 1281, 560, 175, 42, 7, 1,
            // 7795, 10976, 7588, 3416, 1120, 280, 56, 8, 1,
            // 49093, 70155, 49392, 22764, 7686, 2016, 420, 72, 9, 1,
            // 339386, 490930, 350775, 164640, 56910, 15372, 3360, 600, 90, 10, 1,
            // 2554596, 3733246, 2700115, 1286175, 452760, 125202, 28182, 5280, 825, 110, 11, 1,
            // 20794982, 30655152, 22399476, 10800460, 3858525, 1086624, 250404, 48312, 7920, 1100, 132, 12, 1,
            break;


        case 10:  // number of odd values: A000000
            s = W.num_odd_val();
            // 1,
            // 1, 1,
            // 1, 3, 1,
            // 1, 7, 6, 1,
            // 1, 15, 24, 12, 1,
            // 1, 32, 84, 75, 24, 1,
            // 1, 72, 282, 384, 225, 49, 1,
            // 1, 176, 946, 1808, 1617, 680, 106, 1,
            // 1, 470, 3260, 8258, 10239, 6641, 2120, 250, 1,
            // 1, 1370, 11772, 37752, 61035, 54788, 27337, 6904, 648, 1,
            // 1, 4357, 44934, 175754, 355046, 414118, 287276, 114995, 23750, 1842, 1,
            // 1, 15061, 181510, 841975, 2059255, 2990138, 2696466, 1509187, 500270, 86910, 5729, 1,
            // 1, 56232, 775978, 4180843, 12076958, 21152143, 23712773, 17278759, 8047301, 2264090, 338601, 19420, 1,

            break;

//        case xx:  // number of even values: A000000
//            s = W.num_even_val() - 1;  // note: -1
//            // 1,
//            // 1, 1,
//            // 1, 3, 1,
//            // 1, 6, 7, 1,
//            // 1, 12, 24, 15, 1,
//            // ... row reversal of "odd values"
//            break;

        }


        st[ s ] += 1;


#ifndef TIMING
        cout << setw(4) << ct << ":  ";

        // print RGS:
        print_vec("  ", x, n, true );
//        print_vec("    ", A.m_, n, true );

        cout << setw(4) << s;

//        cout << setw(3) << A.num_zeros() << setw(3) << A.num_fixed_points();

//        cout << setw(4) << j;

        cout << endl;

        jjassert( A.OK() );
#endif  // TIMING
    }
    while ( (j=A.next()) );


    ulong sct = 0;
    for (ulong k=0; k<n; ++k)
    {
        cout << st[k] << ", ";
        sct += st[k];
    }
    cout << endl;

    cout << " ct=" << ct;  // total: OEIS sequence A022493
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

Ascent sequences by maximal element (A218577):
1,
1, 1,
1, 3, 1,
1, 7, 6, 1,
1, 15, 25, 11, 1,
1, 31, 90, 74, 20, 1,
1, 63, 301, 402, 209, 37, 1,
1, 127, 966, 1951, 1629, 590, 70, 1,
1, 255, 3025, 8869, 10839, 6430, 1685, 135, 1,
1, 511, 9330, 38720, 65720, 56878, 25313, 4870, 264, 1,
1, 1023, 28501, 164676, 376114, 444337, 292695, 99996, 14209, 521, 1,


Ascent sequences by number of ascents (A137251):
1,
1, 1,
1, 3, 1,
1, 6, 7, 1,
1, 10, 26, 15, 1,
1, 15, 71, 98, 31, 1,
1, 21, 161, 425, 342, 63, 1,
1, 28, 322, 1433, 2285, 1138, 127, 1,
1, 36, 588, 4066, 11210, 11413, 3670, 255, 1,
1, 45, 1002, 10165, 44443, 79781, 54073, 11586, 511, 1,
1, 55, 1617, 23056, 150546, 434638, 528690, 246409, 36038, 1023, 1,


Ascent sequences by number of fixed points; same as: by number of zeros (A175579):
1,
1, 1,
2, 2, 1,
5, 6, 3, 1,
15, 21, 12, 4, 1,
53, 84, 54, 20, 5, 1,
217, 380, 270, 110, 30, 6, 1,
1014, 1926, 1490, 660, 195, 42, 7, 1,
5335, 10840, 9020, 4300, 1365, 315, 56, 8, 1,
31240, 67195, 59550, 30290, 10255, 2520, 476, 72, 9, 1,
201608, 455379, 426405, 229740, 82425, 21448, 4284, 684, 90, 10, 1,


Ascent sequences by position of last zero (A218579):
1,
1, 1,
2, 1, 2,
5, 2, 3, 5,
15, 5, 8, 10, 15,
53, 15, 26, 32, 38, 53,
217, 53, 99, 122, 142, 164, 217,
1014, 217, 433, 537, 619, 704, 797, 1014,
5335, 1014, 2143, 2683, 3069, 3464, 3876, 4321, 5335,
31240, 5335, 11854, 15015, 17063, 19140, 21294, 23522, 25905, 31240,
201608, 31240, 72530, 93084, 105203, 117348, 129960, 142901, 156224, 170368, 201608,


Ascent sequences by position of first occurrence of max (A218580):
1,
1, 1,
1, 2, 2,
1, 4, 5, 5,
1, 8, 13, 15, 16,
1, 16, 35, 47, 56, 62,
1, 32, 97, 153, 204, 248, 279,
1, 64, 275, 515, 770, 1030, 1257, 1423,
1, 128, 793, 1785, 3000, 4424, 5869, 7140, 8100,
1, 256, 2315, 6347, 12026, 19582, 28293, 37058, 44843, 50887,
1, 512, 6817, 23073, 49464, 89048, 140365, 198270, 256341, 308407, 349776,
1, 1024, 20195, 85475, 208250, 414910, 714597, 1090214, 1508225, 1926753, 2305137, 2611722,


Ascent sequences by position of last occurrence of max (A218581):
1,
0, 2,
0, 1, 4,
0, 1, 4, 10,
0, 1, 6, 15, 31,
0, 1, 10, 29, 62, 115,
0, 1, 18, 63, 148, 288, 496,
0, 1, 34, 149, 392, 826, 1496, 2437,
0, 1, 66, 375, 1120, 2592, 5036, 8615, 13435,
0, 1, 130, 989, 3392, 8698, 18332, 33391, 54548, 82127,
0, 1, 258, 2703, 10768, 30768, 70868, 138635, 239688, 377001, 551384,

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A218577-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A218577-demo.cc DEMOFLAGS=-DTIMING"
/// End:

