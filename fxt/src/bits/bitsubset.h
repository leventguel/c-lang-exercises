#if !defined HAVE_BITSUBSET_H__
#define      HAVE_BITSUBSET_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class bit_subset
// Generate all all subsets of bits of  a given word.
//
// e.g. for the word ('.' printed for unset bits)
//   ...11.1.
// these words are produced by subsequent next()-calls:
//   ......1.
//   ....1...
//   ....1.1.
//   ...1....
//   ...1..1.
//   ...11...
//   ...11.1.
//   ........
//
{
public:
    ulong u_;  // current subset
    ulong v_;  // the full set

public:
    explicit bit_subset(ulong v) : u_(0), v_(v)  { ; }
    virtual ~bit_subset()  { ; }
    ulong current()  const  { return u_; }
    ulong next()  { u_ = (u_ - v_) & v_;  return u_; }
    ulong prev()  { u_ = (u_ - 1 ) & v_;  return u_; }

    ulong first(ulong v)  { v_=v;  u_=0;  return u_; }
    ulong first()  { first(v_);  return u_; }

    ulong last(ulong v)  { v_=v;  u_=v;  return u_; }
    ulong last()  { last(v_);  return u_; }
};
// -------------------------


#endif  // !defined HAVE_BITSUBSET_H__
