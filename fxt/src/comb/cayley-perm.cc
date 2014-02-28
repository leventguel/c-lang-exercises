// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/cayley-perm.h"

#include "fxtio.h"
#include "fxttypes.h"

void
cayley_perm::print_arrangement(const char *bla, bool b1/*=true*/)  const
{
    if ( bla )  cout << bla;

    for (ulong j=0; j<n_; ++j)
    {
        cout << j + b1;
        if ( j < n_ - 1 )
        {
            long d = (long)(a_[j+1] - a_[j]);  // jjcast
            if ( d==0 )  cout << " = ";
            else if ( d > 0 )  cout << " < ";
            else  cout << " > ";
        }
    }
}
// -------------------------


