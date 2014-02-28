#if !defined HAVE_TESTNUM_H__
#define      HAVE_TESTNUM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "sort/bsearch.h"
#include "fxttypes.h"

// mod/testnum.cc:
extern const ulong idoneal_tab[];
extern const ulong idoneal_tab_len;
extern const ulong npqr_tab[];
extern const ulong npqr_tab_len;

inline bool is_idoneal(ulong x)
// Return true if the number x is idoneal
{
    ulong idx = bsearch(idoneal_tab, idoneal_tab_len, x);
    return  ( idoneal_tab_len != idx );
}
// -------------------------


inline ulong is_npqr(ulong x)
// Return true if the number x is a modulus such
// that no squares mod x are primes.
{
    ulong idx = bsearch(npqr_tab, npqr_tab_len, x);
    return  ( npqr_tab_len != idx );
}
// -------------------------


#endif  // !defined HAVE_TESTNUM_H__
