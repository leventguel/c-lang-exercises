#if !defined HAVE_BIN_TO_SL_GRAY_H__
#define      HAVE_BIN_TO_SL_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"



static inline ulong bin_to_sl_gray(ulong k, ulong ldn)
// Convert binary number to corresponding word in SL-Gray order.
// Successive transitions are adjacent (one-close) or three-close.
{
    ulong n = 1UL << (ldn-1);
    ulong m = (n<<1) - 1;
    ulong z = n;  --k;  // forward order
//    ulong z = 0;  ++k;  // reverse order
    while ( ldn!=0 )
    {
        const ulong h = k & n;
        z ^= h;

        if ( !h )  k ^= m;

        ++k;  // SL-Gray
//        k = -k - 2;  // complement of SL-Gray

//        k = -k - 1;  // binary reflected Gray code
        // when k is not  changed here ==> complement of binary reflected Gray code

//        k += m/4;  // rotated SL-Gray

//        --k;  // another Gray code
//        k = -k;  // complement of the above

        n >>= 1;
        m >>= 1;
        --ldn;
    }

    return z;
}
// -------------------------


#endif  // !defined HAVE_BIN_TO_SL_GRAY_H__
