
#include "comb/partition.h"

//#include "aux0/factorial.h"

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% OEIS sequence A217605:
//% Number of partitions that are fixed points of a certain map.

// Cf. comb/partition-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 16;
    NXARG(n, "Partitions of n");
    bool sq = 0;
    NXARG(sq, "Whether to print in partitions in falling order");
    partition P(n);

    ulong *Z = new ulong[n+1];  // scratch space
    for (ulong j=0; j<=n; ++j)  Z[j] = 0;

    ulong ct = 0;

    do
    {
//        if ( P.num_of(1) == 0 )  { ct += 1; }  // A002865
//        if ( P.num_of(2) == 0 )  { ct += 1; }  // A027336

//        if ( P.num_of(1) == 0 )  { ct += P.num_of(3); }  // A182713
//        if ( P.num_of(1) == P.num_of(2) )  { ct += 1; }  // A174455
//        if ( P.num_of(1) != P.num_of(2) )  { continue; }  // A174455 (show partitions)

//        if ( P.num_of(1) != 0 )  continue;
//        { ulong m=2; while ( P.num_of(m) == 0 )  { ++m; };  ct += m; }

//        { ulong m=1; while ( P.num_of(m) == 0 )  { ++m; }; ct += (n-m*P.num_of(m)); }
//        { ulong m=; while ( P.num_of(m) == 0 )  { ++m; }; ct += (n-m*P.num_of(m)); }

//        { const ulong *d = P.data();
//            ulong k;
//            for (k=2; k<=n; ++k)
//                if ( d[k] > d[k-1]  )  break;   // A007294
//            ct += (k>n);
//        }

//        ct += (  P.num_parts() == P.num_sorts() );  // A000009
//        ct += (  P.num_parts() != P.num_sorts() );  // A047967

//        { long s = 0;  // number of even vs. number of odd terms
//            for (ulong k=1; k<=n; k+=2)  s += P.num_of(k);
//            for (ulong k=2; k<=n; k+=2)  s -= P.num_of(k);
//
//            ct += (s==0);  // A045931
//            ct += (s>=0);  // A130780
//            ct += (s<0);  // A108949
//            ct += (s<=0);  // A171966
//            ct += (s>0);  // A108950
//            ct += (s==1);  // A000000
//            ct += (s==-1);  // A000000 (as above, shifted right)
//        }

//        ct += ( (P.num_parts()&1)==1 );  // A027193
//        ct += ( (P.num_parts()&1)==0 );  // A027187

//        ct += ( (P.num_sorts()&1)==1 );  // A090794
//        ct += ( (P.num_sorts()&1)==0 );  // A092306

//        { long r = P.rank();
//            if ( r==P.num_parts() )  ct += 1; // A000000
//            if ( r>=0 )  ct += 1; // A064174
//            if ( r>0 )  ct += 1; // A064173
//            if ( r>0 )  ct += ( r%2UL==0 );  // A101708
//            if ( r>0 )  ct += ( r%2UL==1 );  // A101707
//            if ( r>=0 )  ct += ( r%2UL==0 );  // A101709
//            ct += ( r==0 );  // A047993
//            ct += ( r==1 );  // A101198
//            ct += ( r==2 );  // A101199
//            ct += ( r==-2 );  // A101199 (by symmetry)
//            ct += ( r==3 );  // A101200
//            ct += ( r==4 );  // A000000
//            ct += ( r==5 );  // A000000
//            if ( ! ( r==2 ) )  continue;  //
//            ct += ( r%2UL==0 ? +1 : -1 );  // A000025
//        }



//        if ( P.num_parts() == 2*P.largest_part() )  { ct += 1; }  // A000000
//        if ( P.num_parts() >= P.largest_part() )  { ct += 1; }  // A064174
//        if ( P.num_parts() < P.largest_part() )  { ct += 1; }  // A064173

//        if ( P.is_dist_parts() )
//        {
//            ct += ( P.num_parts() < P.largest_part() );  // A000000
//            ct += ( P.num_parts() <= P.largest_part() );  // A000009 (all dist.)
//            ct += ( 2 * P.num_parts() == P.largest_part() );  // A000000
//            ct += ( (P.num_parts()%2==0) && (P.largest_part()%2==0) );  // A000000
//            ct += ( P.num_parts()%2==0 );  // A067661
//            ct += ( P.num_parts()%2==1 );  // A067659
//            ct += ( P.num_parts()%2==1 );  // A067659
//            ct += ( P.num_parts()==P.rank() );  // A000000
//        }


// Abramowitz/Stegun order (conjugate partitions):
//        cout << P.largest_part() << ", ";  // A036043
//        cout << P.num_parts() << ", ";  // A049085
//        cout << -P.rank() << ", ";  // A105805
//        cout << P.num_sorts() << ", ";  // A103921 / reversed lines: A115623
// cf. A117194, A117195


//        if ( P.num_parts() == P.largest_part() )  { ct += 1; }  // A047993
//        if ( P.num_parts() != P.largest_part() )  continue;  // A047993
        // A047993: balanced partitions: first element = number of elements.
        // largest part is equal to number of parts.

//        if ( P.num_parts() == P.smallest_part() )  { ct += 1; }  // A006141
        // A006141: balanced partitions: smallest part is equal to number of parts
//        if ( P.num_parts() != P.smallest_part() )  continue;  // A006141


//        { // A098859: Wilf partitions: all multiplicities are distinct
//            for (ulong j=0; j<=n; ++j)  Z[j] = 0;
//            bool q = true;
//            for (ulong k = 1; k<=n; ++k)
//            {
//                ulong ck = P.num_of(k);
//                if ( ck && (Z[ck]!=0) )
//                { q = false;  break; }
//                Z[ck] = 1;
//            }
//            ct += q;
//            if ( !q )  continue;
//        }


//        {  // compositions into distinct parts:
//            if ( ! P.is_dist_parts() )  continue;
//
////            ct += factorial( P.num_parts() );  // A032020: compositions into distinct parts.
//
////            if ( ! P.is_into_odd_parts() )  continue;
////            ct += factorial( P.num_parts() );  // A032021: compositions into distinct odd parts.
//
//            bool q = true;
//            for (ulong k=1; k<=n; ++k)
//                if ( P.num_of(k) && ( (k%3)!=1 ) ) { q = false;  break; }
//            if ( q )  ct += factorial( P.num_parts() );  // A000000: compositions into distinct parts == 1 mod 3.
//
//            continue;
//        }

        { // A217605: fixed points of a certain involution
            bool q = true;
            for (ulong k = 1; k<=n; ++k)
            {
                ulong ck = P.num_of(k);
                if ( ck && (P.num_of(ck) != k) )
                { q = false;  break; }
            }
            ct += q;
            if ( !q )  continue;
        }



#ifndef  TIMING
        cout << setw(4) << ct << ": ";

//        cout << " [" << P.num_parts() << "]  ";
//        cout << " [" << P.num_sorts() << "]  ";
//        cout << " [" << P.rank() << "]  ";
//        cout << " [" << P.num_of(1) << "]  ";

        cout << setw(4) << n;

        const bool szq = true;  // whether to skip zeros with long format
        cout << " == ";
        P.print_long(szq);

        if ( szq )  cout  << endl << "         ";
        cout << "  ==  ";
        if ( sq )  P.print_falling();
        else       P.print();

        cout << endl;

        jjassert( P.OK() );
#endif  // TIMING
    }
    while ( P.next() );


    cout << " ct=" << (long)ct << endl;

    delete [] Z;  // scratch space

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A217605-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A217605-demo.cc DEMOFLAGS=-DTIMING"
/// End:

