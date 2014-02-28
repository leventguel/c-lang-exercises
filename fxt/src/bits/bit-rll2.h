#if !defined  HAVE_BIT_RLL2_H__
#define       HAVE_BIT_RLL2_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"


class bit_rll2
// Run length limited (RLL) words and Fibonacci words.
// The RLL words are in lexicographic order,
// the Fibonacci words are in a minimal change order (Gray code).
{
public:
    ulong w_;  // RLL-word

public:
    bit_rll2()  { first(); }

    void first()
    {
        w_ = 1;
        ulong s = 3;  // max run length + 1
        while ( s <= BITS_PER_LONG )
        {
            w_ |= w_ << s;
            s <<= 1;
        }
    }

    void last()
    {
        first();
        w_ <<= 2;  // shift by max run length
        w_ = ~w_;
    }

    void middle()
    // RLL word corresponding to all-zero Fibonacci word
    {
#if BITS_PER_LONG == 64
        w_ = 0xaaaaaaaaaaaaaaaaUL;
#else
        w_ = 0xaaaaaaaaUL;
#endif
    }

    ulong next()
    {
        ulong x = w_;
        x |= ( (x>>1) & (x>>2) ); // max run length 2
        x ^= (x+1);
        w_ ^= x;
        return w_;
    }

    ulong prev()
    {
        ulong x = ~w_;  // single line different to next()
        x |= ( (x>>1) & (x>>2) ); // max run length 2
        x ^= (x+1);
        w_ ^= x;
        return w_;
    }

    ulong data()  const
    // RLL word (lexicographic order)
    { return w_; }

    ulong fib()  const
    // Fibonacci word (Gray code)
    { return  ~(w_^(w_>>1)); }

    ulong next_fib()  { next();  return fib(); }
    ulong prev_fib()  { prev();  return fib(); }
};
// -------------------------


#endif  // !defined HAVE_BIT_RLL2_H__
