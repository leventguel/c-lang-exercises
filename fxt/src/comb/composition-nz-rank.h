#if !defined  HAVE_COMPOSITION_NZ_RANK_H__
#define       HAVE_COMPOSITION_NZ_RANK_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/graycode.h"  // inverse_gray_code()
#include "fxttypes.h"

//#include "jjassert.h"


inline ulong composition_nz_rank(const ulong *x, ulong m)
// Return rank r of composition x[], 0 <= r < 2**(n-1)
// where n is the sum of all parts.
{
    if ( m==0 )  return 0;

    ulong r = 0;
    ulong b = 1;
    ulong j = m;
    do // read from x[m-1], x[m-2], ..., x[0]
    {
        --j;
        ulong p = x[j];
        while ( --p != 0 )
        {
            r |= b;
            b <<= 1;
        }
        b <<= 1;
    }
    while ( j );

    return  r;
}
// -------------------------


inline ulong composition_nz_unrank(ulong r, ulong *x, ulong n)
// Return number of parts m of generated composition, 1 <= m <= n.
{
    ulong b = 1UL << (n-1);
    r &= (b<<1) - 1;  // take modulo 2**n

    ulong s = 0;
    ulong m = 0;
    while ( s < n )  // write to x[0], x[1], ...
    {
        b >>= 1;
        ulong p = 1;
        while ( r & b )
        {
            ++p;
            b >>= 1;
        }
        x[m] = p;
        s += p;
        ++m;
    }
//    jjassert( s == n );

    return m;
}
// -------------------------


inline ulong composition_nz_rl_rank(const ulong *x, ulong m)
// Return (run-length) rank r of composition x[], 0 <= r < 2**(n-1)
// where n is the sum of all parts.
{
    if ( m==0 )  return 0;

    ulong r = composition_nz_rank(x, m);
    r = ~r;
    r = inverse_gray_code(r);

    ulong s = 0;
    for (ulong j=0; j<m; ++j)  s += x[j];

    if ( (s&1)==0 )  r = ~r;

    r &= (1UL << (s-1)) - 1;

    return  r;
}
// -------------------------


inline ulong composition_nz_rl_unrank(ulong r, ulong *x, ulong n)
// Return number of parts m of generated composition, 1 <= m <= n.
{
    ulong b = 1UL << (n-1);
    r &= (b<<1) - 1;  // take modulo 2**n

    bool v = 0;
    ulong s = 0;
    ulong m = 0;
    while ( s < n )  // write to x[0], x[1], ...
    {
        b >>= 1;
        ulong p = 1;
        while ( ((r & b) ==0) != v )
        {
            if ( b==0 )  break;
            ++p;
            b >>= 1;
        }
        v = ! v;
        x[m] = p;
        s += p;
        ++m;
    }
//    jjassert( s == n );
//    jjassert( r == composition_nz_rl_rank(x, m) );

    return m;
}
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_RANK_H__
