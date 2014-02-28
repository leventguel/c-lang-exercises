// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/composition-nz-left-smooth.h"

#include "fxtio.h"
#include "fxttypes.h"


//void
//composition_nz_left_smooth::print_composition_aa()  const
//{
//    cout << endl;
//
//    ulong mx = 0;
//    for (ulong j=1; j<=m_; ++j)
//        if ( a_[j] > mx )  mx = a_[j];
//
//    for (ulong k=mx; k>0; --k)
//    {
//        cout << ' ';
//
//        ulong kl = 0;  // last occurrence of element >=k
//        for (ulong j=1; j<=m_; ++j)
//            if ( a_[j]>=k )  kl = j;
//
//        for (ulong j=1; j<=kl; ++j)
//        {
//            cout << ( a_[j] >= k ? 'o' : ' ' );
//        }
//        cout << endl;
//    }
//}
//// -------------------------

void
composition_nz_left_smooth::print_fountain_aa()  const
{
    cout << endl;

    ulong mx = 0;
    for (ulong j=1; j<=m_; ++j)
        if ( a_[j] > mx )  mx = a_[j];

    for (ulong k=mx; k>0; --k)
    {
        cout << ' ';

        ulong kl = 0;  // last occurrence of element >=k
        for (ulong j=1; j<=m_; ++j)
            if ( a_[j]>=k )  kl = j;

        for (ulong j=0; j<=mx-k; ++j)  cout << ' ';  // fountain
        for (ulong j=1; j<=kl; ++j)
        {
            cout << ' ';  // fountain
            cout << ( a_[j] >= k ? 'O' : ' ' );
        }
        cout << endl;
    }
}
// -------------------------

