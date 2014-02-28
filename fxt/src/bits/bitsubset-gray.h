#if !defined HAVE_BITSUBSET_GRAY_H__
#define      HAVE_BITSUBSET_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsubset.h"
#include "bits/bithigh.h"
#include "fxttypes.h"

#define BITSUBSET_GRAY_METHOD1  // un/define to choose method (default:=defined)


class bit_subset_gray
// Generate all all subsets of bits of  a given word,
// in Gray code (minimal-change) order.
//
// e.g. for the word ('.' printed for unset bits)
//   ...11.1.
// these words are produced by subsequent next()-calls:
//   ......1.
//   ....1.1.
//   ....1...
//   ...11...
//   ...11.1.
//   ...1..1.
//   ...1....
//   ........
{
public:
    bit_subset S_;
    ulong g_;  // subsets in Gray code order
    ulong h_;  // highest bit in S_.v_;  needed for the prev() method

public:
    explicit bit_subset_gray(ulong v)
       : S_(v), g_(0), h_(highest_one(v))
    { ; }

    virtual ~bit_subset_gray()  { ; }

    ulong current()  const { return g_; }

    ulong next()
    {
        ulong u0 = S_.current();
        if ( u0 == S_.v_ )  return first();
        ulong u1 = S_.next();
#ifdef BITSUBSET_GRAY_METHOD1
        ulong x = ~u0 & u1;
#else
        ulong x = (u0 ^ u1) & u1;
#endif
        g_ ^= x;
        return g_;
    }

    ulong first(ulong v)
    {
        S_.first(v);
        h_=highest_one(v);
        g_=0;
        return g_;
    }

    ulong first()
    {
        S_.first();
        g_=0;
        return g_;
    }

    ulong prev()
    {
        ulong u1 = S_.current();
        if ( u1 == 0 )  return last();
        ulong u0 = S_.prev();
#ifdef BITSUBSET_GRAY_METHOD1
        ulong x = ~u0 & u1;
#else
        ulong x = (u0 ^ u1) & u1;
#endif
        g_ ^= x;
        return g_;
    }

    ulong last(ulong v)
    {
        S_.last(v);
        h_=highest_one(v);
        g_=h_;
        return g_;
    }

    ulong last()
    {
        S_.last();
        g_=h_;
        return g_;
    }
};
// -------------------------

#endif  // !defined HAVE_BITSUBSET_GRAY_H__

