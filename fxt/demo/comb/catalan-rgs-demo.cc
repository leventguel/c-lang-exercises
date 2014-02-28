
#include "comb/catalan-rgs.h"
#include "comb/paren-string-to-rgs.h"
// demo-include "comb/paren-string-to-rgs.cc"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Catalan restricted growth strings (RGS) and
//% parentheses strings in lexicographic order.

//#define TIMING  // uncomment to disable printing

// Cf. comb/motzkin-nonflat-rgs-lex-demo.cc for Motzkin (nonflat) RGS.


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of paren pairs");

    catalan_rgs C(n);

    ulong ct = 0;

#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "With benchmark: whether to generate backward order");

#ifdef CATALAN_RGS_FIXARRAYS
    cout << "CATALAN_RGS_FIXARRAYS is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        C.last();
        do  { ++ct; }  while ( C.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        C.first();
        do  { ++ct; }  while ( C.next() );
    }
#else  // TIMING

    bool rq = 1;
    NXARG(rq, "whether to show RGS for reversed string");

//    C.last();
    const ulong n2 = 2*n;
    ulong j = 0;
    do
    {
#if 0 // disallow flat steps: A086246 and A001006 (Motzkin numbers)
        bool q = 1;
        const ulong *a = C.data();
        for (ulong k=1; k<n; ++k)
            if ( a[k] == a[k-1])  { q=0;  break; };
        if ( ! q )  continue;

#endif

        ++ct;
        cout << setw(4) << ct << ":";

        // print RGS:
        print_vec("    ", C.data(), n, true );

        cout << setw(4) << j;

        // print paren string:
        const char *str = C.paren_string();
        cout << "    " << str;

        // print delta set:
        cout << "    ";
        for (ulong k=0; k<n2; ++k)  cout << ( str[k]=='(' ? '1' : '.' );


//        ulong w2 = 0;  // bit-string representation
//        for (ulong k=0, m=(1UL<<(n2-1));  k<n2;  ++k, m>>=1)
//            if ( str[k]=='(' )  w2 |= m;

        if ( rq )
        {
            char str2[64];
            ulong rgs2[32];

            jjassert( paren_string_to_rgs(str, rgs2) );
            rgs_to_paren_string(rgs2, n, str2, true);
            jjassert( paren_string_to_rgs(str2, rgs2) );

            cout << "    ";
            print_vec("    ", rgs2, n, true);
//            cout << "    " << str2;
            cout << "    ";
            for (ulong k=0; k<n2; ++k)  cout << ( str2[k]=='(' ? '1' : '.' );
            jjassert( paren_string_to_rgs(str2, rgs2) );
        }

        cout << endl;
    }
    while ( (j=C.next()) );
//    while ( (j=C.prev()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Catalan number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18 0
arg 1: 18 == n  [Number of paren pairs]  default=5
arg 2: 0 == bw  [With benchmark: whether to generate backward order]  default=0
forward:
 ct=477638700
./bin 18 0  1.48s user 0.00s system 99% cpu 1.482 total
 ==> 477638700/1.48 == 322,728,851 per second
 // with CATALAN_RGS_FIXARRAYS:
./bin 18 0  1.35s user 0.00s system 99% cpu 1.356 total
 ==> 477638700/1.35 == 353,806,444 per second

 time ./bin 18 1
arg 1: 18 == n  [Number of paren pairs]  default=5
arg 2: 1 == bw  [With benchmark: whether to generate backward order]  default=0
backward:
 ct=477638700
./bin 18 1  2.22s user 0.00s system 99% cpu 2.218 total
 ==> 477638700/2.22 == 215,152,567 per second
 // with CATALAN_RGS_FIXARRAYS:
./bin 18 1  2.32s user 0.00s system 99% cpu 2.321 total
 ==> 477638700/2.32 == 205,878,750 per second

*/

/*
BENCHARGS=18 0
BENCHARGS=18 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

