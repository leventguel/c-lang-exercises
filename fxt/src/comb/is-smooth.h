#if !defined  HAVE_IS_SMOOTH_H__
#define       HAVE_IS_SMOOTH_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_smooth(const ulong *a, ulong n, ulong d=1)
// Return whether a[] is smooth, that is, abs(a[k]-a[k-1]) <= d
{
    if ( n<=1 )  return true;

    for (ulong j=1; j<n; ++j)
    {
        ulong a1 = a[j-1],  a0 = a[j];
        ulong da = ( a0 > a1 ? a0-a1 : a1-a0 );
        if ( da > d )  return false;
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SMOOTH_H__
