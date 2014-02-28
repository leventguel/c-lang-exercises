// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/young-tab-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"


void
young_tab_rgs::print_aa(ulong off/*=1*/)  const
// Render Young tableau as ASCII art.
{
    cout << " ";
    for (ulong j=0; j<st_[0]; ++j)  cout << "--- ";
    cout << endl;

    const ulong h = height();
    for (ulong r=0; r<h; ++r)
    {

        cout << "|";
        for (ulong j=0; j<n_; ++j)
        {
            if ( a_[j] == r )
                cout << setw(2) << (j + off) << " |";
        }
        cout << endl;

        cout << " ";
        for (ulong j=0; j<st_[r]; ++j)  cout << "--- ";
        cout << endl;
    }
}
// -------------------------
