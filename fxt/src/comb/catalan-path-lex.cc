// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/catalan-path-lex.h"

#include "fxtio.h"
#include "fxttypes.h"

void
catalan_path_lex::print_aa()  const
// Render path as ASCII art.
{
#ifdef CATALAN_PATH_LEX_NO_FLAT_STEPS
    for (ulong k=1;  k<=n_;  ++k)
    {
        cout << ' ';
        const ulong ak = a_[k],  ak1 = a_[k-1];
        const bool rq = ( ak > ak1 );  // rise?
        for (ulong j=1; j < ak+!rq; ++j)  cout << ' ';
        cout << ( rq ? '\\' : '/' );
        cout << endl;
    }
#else

    for (ulong k=1;  k<=n_;  ++k)
    {
        cout << ' ';
        const ulong ak = a_[k],  ak1 = a_[k-1];
        const bool rq = ( ak > ak1 );  // rise?
        for (ulong j=1; j < ak+!rq; ++j)  cout << ' ';
        cout << ( rq ? '\\' : ( ak==ak1 ? '|' : '/' ) );
        cout << endl;
    }
#endif
}
// -------------------------

