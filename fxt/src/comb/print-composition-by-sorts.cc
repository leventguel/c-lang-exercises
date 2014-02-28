
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxtio.h"
#include "fxttypes.h"

void
print_composition_by_sorts(const ulong *va, const ulong *vs, ulong m)
{
    cout << "[ ";
    ulong ct = 0;
    ulong s = 0;
    while ( ct < m )
    {
        cout << "[ ";
        for (ulong j=0; j<m; ++j)
        {
            if ( vs[j] == s )
            {
                cout << va[j] << " ";
                ++ct;
            }
        }
        cout << "]  ";
        ++s;
    }
    cout << "]";
}
// -------------------------
