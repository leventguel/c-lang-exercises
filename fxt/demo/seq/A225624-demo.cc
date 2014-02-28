
#include "comb/descent-rgs.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% OEIS sequence A225624:
//% triangle, length-n descent sequences with k-1 descents.
//% A descent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//%   d(k)>=0, and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.)
//%   counts the number of descents of its argument.

// Cf. seq/A218577-demo.cc for stats for ascent sequences
// Cf. comb/descent-rgs-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings, n>=1");
    jjassert( n>=1 );  // else word_stats will not work
    ulong sq = 1;
    NXARG(sq, "Select stats:\n"
          "    0 ==> max element\n"
          "    1 ==> number of descents\n"
          "    2 ==> number of ascents\n"
          "    3 ==> number of zeros - 1\n"
          "    4 ==> number of maximal digits - 1\n"
          "    5 ==> number of fixed points - 1\n"
          "    6 ==> position of last occurrence of zero\n"
          "    7 ==> position of first occurrence of the maximal value\n"
          "    8 ==> position of last occurrence of the maximal value\n"
          "    9 ==> number of flat steps\n"
          "   10 ==> number of odd values\n"
//          "   11 ==> number of \n"
          );

    descent_rgs A(n);
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
        ++ct;
        ulong s = 0;
        switch ( sq )
        {
        case 0:  // by max element: A000000
            s = W.max_val();
            break;
            // 1,
            // 1, 1,
            // 1, 3, 0,
            // 1, 7, 1, 0,
            // 1, 15, 7, 0, 0,
            // 1, 31, 32, 3, 0, 0,
            // 1, 63, 122, 35, 1, 0, 0,
            // 1, 127, 423, 249, 32, 0, 0, 0,
            // 1, 255, 1389, 1413, 421, 22, 0, 0, 0,
            // 1, 511, 4414, 7078, 3789, 606, 13, 0, 0, 0,
            // 1, 1023, 13744, 32898, 27738, 8859, 794, 5, 0, 0, 0,
            // 1, 2047, 42245, 145854, 179415, 94394, 19131, 925, 1, 0, 0, 0,

        case 1:  // by number of descents: A000000
            s = A.num_descents();  // simplified: s==A.m[n-1]
//            jjassert( s == W.num_ascents() );
            break;
            // 1,
            // 2, 0,
            // 3, 1, 0,
            // 4, 5, 0, 0,
            // 5, 15, 3, 0, 0,
            // 6, 35, 25, 1, 0, 0,
            // 7, 70, 117, 28, 0, 0, 0,
            // 8, 126, 405, 271, 22, 0, 0, 0,
            // 9, 210, 1155, 1631, 483, 13, 0, 0, 0,
            // 10, 330, 2871, 7359, 5126, 711, 5, 0, 0, 0,
            // 11, 495, 6435, 27223, 36526, 13482, 889, 1, 0, 0, 0,
            // 12, 715, 13299, 86919, 199924, 151276, 30906, 962, 0, 0, 0, 0,

        case 2:  // by number of ascents: A000000
            s = W.num_ascents();
            break;
            // 1,
            // 1, 1,
            // 1, 3, 0,
            // 1, 6, 2, 0,
            // 1, 10, 11, 1, 0,
            // 1, 15, 36, 15, 0, 0,
            // 1, 21, 91, 97, 12, 0, 0,
            // 1, 28, 196, 421, 180, 6, 0, 0,
            // 1, 36, 378, 1435, 1411, 239, 1, 0, 0,
            // 1, 45, 672, 4148, 7821, 3506, 219, 0, 0, 0,
            // 1, 55, 1122, 10626, 34634, 31982, 6506, 136, 0, 0, 0,
            // 1, 66, 1782, 24805, 130729, 217829, 99620, 9129, 52, 0, 0, 0,
            // second col: A000217, g.f. x/(1-x)^3
            // third col: A005583, g.f.: x*(2-x)/(1-x)^6

        case 3:  // by number of zeros: A000000
            s = W.num_zeros() - 1;  // note: -1
//            jjassert( s == W.num_min_val() - 1 );
            break;
            // 1,
            // 1, 1,
            // 1, 2, 1,
            // 1, 4, 3, 1,
            // 1, 8, 9, 4, 1,
            // 1, 17, 27, 16, 5, 1,
            // 1, 40, 85, 64, 25, 6, 1,
            // 1, 107, 289, 266, 125, 36, 7, 1,
            // 1, 329, 1078, 1174, 645, 216, 49, 8, 1,
            // 1, 1161, 4440, 5567, 3495, 1331, 343, 64, 9, 1,
            // 1, 4662, 20201, 28515, 20076, 8546, 2457, 512, 81, 10, 1,
            // 1, 21074, 101226, 157996, 122828, 57632, 18235, 4180, 729, 100, 11, 1,

        case 4:  // by number of max digits: A000000
            s = W.num_max_val() - 1;  // note: -1
            break;
            // 1,
            // 1, 1,
            // 2, 1, 1,
            // 4, 3, 1, 1,
            // 10, 7, 4, 1, 1,
            // 31, 18, 11, 5, 1, 1,
            // 111, 57, 30, 16, 6, 1, 1,
            // 444, 213, 97, 47, 22, 7, 1, 1,
            // 1969, 892, 375, 156, 70, 29, 8, 1, 1,
            // 9643, 4123, 1638, 620, 240, 100, 37, 9, 1, 1,
            // 51864, 20985, 7871, 2813, 977, 356, 138, 46, 10, 1, 1,
            // 304526, 117141, 41485, 14028, 4585, 1482, 512, 185, 56, 11, 1, 1,

        case 5:  // by number of fixed points: A000000
            s = W.num_fixed_points() - 1;  // note: -1
            break;
            // 1,
            // 1, 1,
            // 2, 2, 0,
            // 4, 5, 0, 0,
            // 9, 14, 0, 0, 0,
            // 23, 44, 0, 0, 0, 0,
            // 67, 155, 0, 0, 0, 0, 0,
            // 222, 610, 0, 0, 0, 0, 0, 0,
            // 832, 2669, 0, 0, 0, 0, 0, 0, 0,
            // 3501, 12911, 0, 0, 0, 0, 0, 0, 0, 0,
            // 16412, 68650, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 85062, 398951, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 484013, 2520329, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 6:  // position of last zero: A000000
            s = W.last_zero_idx();
//            jjassert( s == W.last_min_idx() );
            break;

        case 7:  // position of first occurrence of max: A000000
            s = W.first_max_idx();
            break;

        case 8:  // position of last occurrence of max: A000000
            s = W.last_max_idx();
            break;

        case 9:  // number of flat steps: A000000
            s = W.num_flat_steps();
            break;


        case 10:  // number of odd values: A000000
            s = W.num_odd_val();
            break;

//        case xx:  // number of even values: A000000
//            s = W.num_even_val() - 1;  // note: -1
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

    cout << " ct=" << ct;  // total: OEIS sequence A225588
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

 for n in $(seq 1 13) ; do ./bin $n 1 | grep ', $' ; done


Descent sequences by number of descents (A225624):
1,
2, 0,
3, 1, 0,
4, 5, 0, 0,
5, 15, 3, 0, 0,
6, 35, 25, 1, 0, 0,
7, 70, 117, 28, 0, 0, 0,
8, 126, 405, 271, 22, 0, 0, 0,
9, 210, 1155, 1631, 483, 13, 0, 0, 0,
10, 330, 2871, 7359, 5126, 711, 5, 0, 0, 0,
11, 495, 6435, 27223, 36526, 13482, 889, 1, 0, 0, 0,
12, 715, 13299, 86919, 199924, 151276, 30906, 962, 0, 0, 0, 0,
13, 1001, 25740, 247508, 903511, 1216203, 546001, 63462, 903, 0, 0, 0, 0,


*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A225624-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A225624-demo.cc DEMOFLAGS=-DTIMING"
/// End:

