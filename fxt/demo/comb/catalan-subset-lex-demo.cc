
#include "comb/catalan-subset-lex.h"

#include "comb/reverse-paren-string.h"
#include "comb/is-paren-string.h"
#include "comb/is-catalan-rgs.h"

#include "comb/paren-string-to-rgs.h"
#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Catalan restricted growth strings (RGS) and parentheses strings in subset-lex order.

// Cf. comb/catalan-gslex-demo.cc for gslex order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
#ifdef CATALAN_SUBSET_LEX_SC
    NXARG(n, "Number of paren pairs");
#else
    NXARG(n, "Number of paren pairs (n>=2)");
    jjassert( n>=2 );
#endif

    catalan_subset_lex C(n);
    bool bw = 0;
    NXARG(bw, "Whether to generate backward order");
    if ( bw )  C.last();

    ulong ct = 0;
#ifdef TIMING
#ifdef CATALAN_SUBSET_LEX_SC
    cout << "CATALAN_SUBSET_LEX_SC is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        do  { ++ct; }  while ( C.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        do  { ++ct; }  while ( C.next() );
    }

#else  // TIMING

    ulong *rgs2 = new ulong[n];  // RGS for reversed strings
    const ulong n2 = 2*n;
    char *str2 = new char[n2+1];  // for reversed strings
    str2[n2] = 0;

    bool q;
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";

        print_vec("    ", C.data(), n, true);

        cout << setw(4) << C.tr_;

        const char *str = C.bit_string();
        cout << "    " << str;

//        cout << "    " << C.paren_string();

#if 1  // show reversed paren-string and its RGS
        reverse_paren_string(str, n2, str2);  // reversed string
        paren_string_to_rgs( str2, rgs2 );  // "reversed" RGS
        print_vec("    ", rgs2, n, true);
        cout << "    ";
        cout << str2;
        jjassert( is_catalan_rgs(rgs2, n) );
        jjassert( is_paren_string(str2, n2) );
#endif

        cout << endl;

        q = ( bw ? C.prev() : C.next() );
    }
    while ( q );

    delete [] rgs2;
    delete [] str2;

#endif  // TIMING

    cout << " ct=" << ct;  // Catalan number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19 0
CATALAN_SUBSET_LEX_SC is defined
forward:
 ct=1767263190
./bin 19 0  4.34s user 0.00s system 99% cpu 4.346 total
 ==> 1767263190/4.34 == 407,203,500 per second

// when CATALAN_SUBSET_LEX_SC is not defined:
./bin 19 0  4.52s user 0.00s system 99% cpu 4.529 total


 time ./bin 19 1
CATALAN_SUBSET_LEX_SC is defined
backward:
 ct=1767263190
./bin 19 1  3.31s user 0.00s system 99% cpu 3.312 total
 ==> 1767263190/3.31 == 533,916,371 per second

// when CATALAN_SUBSET_LEX_SC is not defined:
./bin 19 1  3.55s user 0.00s system 99% cpu 3.549 total

*/

/*
BENCHARGS=19 0
BENCHARGS=19 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

