// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/setpart-rgs-gray.h"

#include "sort/minmaxmed23.h"  // max2()

#include "fxtio.h"
#include "fxttypes.h"


void
setpart_rgs_gray::print()  const
{
//    const char sep[]=", ";
    const char sep[]=" ";
    ulong n = n_;

    cout << "s[ ";
    for (ulong j=0; j<n; ++j)  cout << s_[j] << sep;
    cout << "]";

    cout << "    m[ ";
    for (ulong j=1; j<=n; ++j)  cout << m_[j] << sep;
    cout << "]";

    cout << "    d[ ";
    for (ulong j=0; j<n; ++j)  cout << (d_[j]==1UL ? '+' : '-') << sep;
    cout << "]";
}
// -------------------------


void
setpart_rgs_gray::print_set(ulong off/*=1*/)  const
{
    const ulong ns = m_[n_];  // number of sets
    for (ulong s=0; s<ns; ++s)
    {
        cout << "{";
        ulong u = 0;
        for (ulong k=0; k<n_; ++k)  u += (s_[k]==s );

        for (ulong k=0; k<n_; ++k)
        {
            if ( s_[k] == s )
            {
                cout << (k+off);
                if ( --u )  cout << ", ";
            }
        }
        cout << "}";
        if ( s+1<ns )  cout << ", ";
    }
}
// -------------------------
