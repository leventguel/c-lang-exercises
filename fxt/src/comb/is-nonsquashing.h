#if !defined  HAVE_IS_NONSQUASHING_H__
#define       HAVE_IS_NONSQUASHING_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline bool is_nonsquashing(const ulong *a, ulong m)
// Return whether a[k] >= sum(j=k+1..m-1, a[j] )
{
    if ( m<=1 )  return true;
    ulong w = 0;
    ulong j = m - 1;
    do
    {
        ulong v = a[j];
        if ( w > v )  return false; // non-squashing, cf. A018819
//        if ( w>=v )  return false; // strongly decreasing, cf. A040039
        w += v;
    }
    while ( j-- );
    return true;
}
// -------------------------


inline bool is_strongly_decreasing(const ulong *a, ulong m)
// Return whether a[k] > sum(j=k+1..m-1, a[j] )
{
    if ( m<=1 )  return true;
    ulong w = 0;
    ulong j = m - 1;
    do
    {
        ulong v = a[j];
//        if ( w > v )  return false; // non-squashing, cf. A018819
        if ( w>=v )  return false; // strongly decreasing, cf. A040039
        w += v;
    }
    while ( j-- );
    return true;
}
// -------------------------

#endif // !defined HAVE_IS_NONSQUASHING_H__
