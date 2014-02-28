#if !defined  HAVE_BINOMIAL_H__
#define       HAVE_BINOMIAL_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline ulong binomial(ulong n, ulong k)
{
    if ( k>n )  return  0;
    if ( (k==0) || (k==n) )  return  1;
    if ( 2*k > n )  k = n-k;  // use symmetry

    ulong b = n - k + 1;
    ulong f = b;
    for (ulong j=2; j<=k; ++j)
    {
        ++f;
        b *= f;
        b /= j;
    }
    return  b;
}
// -------------------------


#endif  // !defined HAVE_BINOMIAL_H__
