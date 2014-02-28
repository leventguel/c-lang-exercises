#if !defined  HAVE_IS_SETPART_RGS_H__
#define       HAVE_IS_SETPART_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline bool is_setpart_rgs(const ulong *x, ulong n)
// Return whether x[0,1,...,n-1] is a valid RGS of a set partition.
{
    if ( n == 0 )  return true;  // Nothing to check

    ulong mx = x[0];  // maximum of prefix
    if ( mx != 0 )  return false;

    for (ulong j=1; j<n; ++j)
    {
        const ulong aj = x[j];
        if ( aj > mx )
        {
            ++mx;
            if ( aj > mx )  return false;
        }
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SETPART_RGS_H__
