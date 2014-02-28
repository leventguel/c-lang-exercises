// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/rgs-maxincr.h"
#include "fxtio.h"
#include "fxttypes.h"

void
rgs_maxincr::print(bool nsq/*=false*/)  const
{
    cout << "[ ";
    for (ulong j=0; j<n_; ++j)  cout << s_[j] << " ";
    cout << "]";

    if ( nsq )
    {
        cout << "    [ ";
        for (ulong j=0; j<n_; ++j)  cout << m_[j] << " ";
        cout << "]";
    }
}
// -------------------------

