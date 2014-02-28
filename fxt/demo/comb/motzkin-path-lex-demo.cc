
#include "comb/motzkin-path-lex.h"

#include "comb/is-motzkin-path.h"
#include "comb/is-schroeder-path.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Motzkin paths in lexicographic order, CAT algorithm.
//% Cf. OEIS sequence A001006.

// 1, 1, 2, 4, 9, 21, 51, 127, 323, 835, 2188, 5798, 15511, 41835, 113634, ...


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of paths (n>=1)");
    jjassert( n>=1 );

    motzkin_path_lex M(n);

    ulong ct = 0;

#ifdef TIMING
    do { ++ct; } while ( M.next() );
#else

    const ulong *x = M.data();
    ulong j = 0;
    do
    {
#if 0
            // only Schroeder paths (n should be *even*):
            // A006318: Large Schroeder numbers.
            //   1, 2, 6, 22, 90, 394, 1806, 8558, 41586, ...
            if ( ! is_schroeder_path(x, n) )  continue;

//            bool q = true;
//            for (ulong i=1; i<n; ++i)  // no peaks at height 1
//            {
//                if ( (x[i]==1) && (x[i-1]==0) && (x[i+1]==0 ) )
//                      { q = false; break; }
//            }
//            if ( ! q )  continue;
#endif

        ++ct;

        cout << setw(4) << ct << ":  ";
        M.print("    ", true );
        cout << "    " << setw(2) << j;

        cout << "    ";
        for (ulong i=1; i<=n; ++i)
        {
            ulong d = x[i] - x[i-1] + 1;
            cout << " " << "-0+"[d];
//            cout << " " << ")x("[d];
//            cout << " " << "DhU"[d];
//            cout << " " << "\\-/"[d];
        }


        cout << endl;

//        jjassert( is_motzkin_path(x, n) );
    }
    while ( (j=M.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 23
 ct=1129760415
./bin 23  5.10s user 0.00s system 99% cpu 5.104 total
 ==> 1129760415/5.10 == 221,521,650 per second

// without "easy case" optimization:
./bin 23  7.00s user 0.00s system 99% cpu 7.003 total
 ==> 1129760415/7.00 == 161,394,345 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/motzkin-path-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/motzkin-path-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
