
#include "comb/partition-desc.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions as non-increasing list of parts.
//% Same as: compositions into non-increasing parts.
//% Cf. OEIS sequence A000041.

// Cf. comb/partition-asc-demo.cc for partitions as non-decreasing lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "integer partitions of n");

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    partition_desc P(n);

    ulong ct = 0;


#ifdef TIMING
#ifdef PARTITION_DESC_FIXARRAYS
    cout << "PARTITION_DESC_FIXARRAYS is defined" << endl;
#endif
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0  // only into self-conjugate partitions
        if ( !partition_desc_is_self_conj( P.data(), m ) )  continue;
#endif
#if 0  // modulo conditions:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=0; j<m; ++j)
        { ulong v=x[j];
//            v%=5; if ( (v!=1) && (v!=4) )  // A003114
//            v%=5; if ( (v!=2) && (v!=3) )  // A003106
//            v%=5; if ( (v!=2) && (v!=1) )  // A035371
//            v%=4; if ( (v!=2) && (v!=1) )  // A035365
//            v%=4; if ( (v!=1) )  // A035451
            v%=4; if ( (v==0) )  // A001935
            { q=false; break; }
        }
        if ( !q )  continue;
#endif
#if 0  // growth conditions:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)  // all but first part even
            if ( 0!=(x[j]%2) )  { q=false; break; }  // A119620
        if ( !q )  continue;
#endif
#if 0  // growth conditions:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)
        {
//            if ( x[j-1] >= 2 * x[j] )  // A000000
            if ( x[j-1] > 2 * x[j] )  // A000000
//            if ( x[j-1] - x[j] > 1 )  // A034296 (flat partitions)
//            if ( x[j-1] - x[j] > 2 )  // A224956
//            if ( x[j-1] - x[j] < 2 )  // A003114
//            if ( x[j-1] - x[j] < 3 )  // A025157
//            if ( (x[j-1] - x[j])%2==0  )  // A179080
//            if ( (x[j-1] - x[j])%2==1  )  // A096441

            { q=false; break; }
        }
        if ( !q )  continue;
#endif
#if 0  // all parts (except the largest) may appear only once:
        const ulong *x = P.data();
        bool q = true;
        ulong x0 = x[0];
        { ulong j=1;  while ( (x[j]==x0) && (j<m) )  ++j;
            for ( ; j<m; ++j)
            {
                if ( x[j-1] == x[j] )  // A034296
                { q=false; break; }
            }
        }
        if ( !q )  continue;
#endif
//        if ( 0!=(P.data()[m-1]&1) )  continue; // least part even: A026805
//        if ( 0!=(m&1) )  continue; // even number of parts: A027187
//        if ( 0!=(P.data()[0]&1) )  continue; // largest part even: A027187 (==even num parts)
        // even num & largest even: A000000 (not in the OEIS)

//        if ( 0==(P.data()[m-1]&1) )  continue; // least part odd: A026804
//        if ( 0==(m&1) )  continue; // odd number of parts: A027193
//        if ( 0==(P.data()[0]&1) )  continue; // largest part odd: A027193 (==odd num parts)
        // odd num & largest odd: A000000 (not in the OEIS)


        ++ct;
//        cout << "[" << setw(2) << ct << "]";  // format for OEIS examples
        cout << setw(4) << ct << ": ";
        cout << " [" << setw(2) << m << "] ";

//        cout << " d=" << setw(2) << P.durfee_n() << " ";


//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";
//        cout << " [" << setw(2) << P.s_ << "] ";

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

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

 time ./bin 115
arg 1: 115 == n  [integer partitions of n]  default=10
  ct=1064144451
./bin 115  3.69s user 0.00s system 99% cpu 3.689 total
 ==> 1064144451/3.69 == 288,386,030 per second

With PARTITION_DESC_FIXARRAYS: (slowdown)

*/

/*
BENCHARGS=115
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

