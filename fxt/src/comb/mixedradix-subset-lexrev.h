#if !defined HAVE_MIXEDRADIX_SUBSET_LEXREV_H__
#define      HAVE_MIXEDRADIX_SUBSET_LEXREV_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

#define MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS  // default on

class mixedradix_subset_lexrev
// Mixed radix numbers in reversed subset-lexicographic order.
// Words are reversed with respect to subset-lexicographic order.
// Successive numbers differ in at most three digits.
{
public:
    ulong n_;   // Number of digits (n kinds of elements in multiset)
    ulong tr_;  // aux: current track
#ifndef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
    ulong *a_;  // digits of mixed radix number (multiplicity of kind k in subset).
    ulong *m1_;  // nines (radix minus one) for each digit (multiplicity of kind k in set).
#else
    ulong a_[64];
    ulong m1_[64];
#endif

private:  // have pointer data
    mixedradix_subset_lexrev(const mixedradix_subset_lexrev&);  // forbidden
    mixedradix_subset_lexrev & operator = (const mixedradix_subset_lexrev&);  // forbidden

public:
    explicit mixedradix_subset_lexrev(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        bool z = ( n_ == 0 );
#ifndef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
        a_ = new ulong[n_ + 1 + z];
        m1_ = new ulong[n_ + z];
#endif
        a_[n_] = 1;  // sentinel to stop scan to the right

        if ( z )  // n==0 treated as 1-digit number with radix 1
        {
            a_[0] = 0;
            a_[1] = 1;  // !=0
            m1_[0] = 0;  // <= a[0]
        }
        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    virtual ~mixedradix_subset_lexrev()
    {
#ifndef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
        delete [] a_;
        delete [] m1_;
#endif
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = (n_ ? n_-1 : 0);
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        a_[0] = m1_[0];
        tr_ = 0;
    }

    bool next()
    // Generate next.
    // Return false if current was last.
    {
        ulong j = tr_;
        if ( a_[j] < m1_[j] )  // easy case
        {
            ++a_[j];
            return true;
        }

        // here a_[j] == m1_[j]
        if ( j != 0 )  // semi-easy case: move track to the left
        {
            --j;
            a_[j] = 1;
            tr_ = j;
            return true;
        }

        a_[j] = 0;

        // find first nonzero digit to the right:
        ++j;
        while ( a_[j] == 0 )  { ++j; }  // may read sentinel a[n]

        if ( j >= n_ )  return false;  // current is last

        --a_[j];  // decrement digit to the right
        --j;
        a_[j] = 1;
        tr_ = j;
        return true;
    }

    bool prev()
    // Generate previous.
    // Return false if current was first.
    // Loopless algorithm.
    {
        ulong j = tr_;
        if ( a_[j] > 1 )  // easy case
        {
            --a_[j];
            return true;
        }

        ulong tr1 = tr_ + 1;
        if ( tr1 >= n_ )
        {
#if 1 // optimization
            bool q = ( a_[tr_] != 0 );
            a_[tr_] = 0;
            return q;
#else
            if ( a_[tr_] == 0 )  return false;  // current is first
            a_[tr_] = 0;  // now word is first (all zero)
            return true;
#endif
        }

        a_[j] = 0;

        ++j;  // now looking at next track to the right
        if ( a_[j] == m1_[j] )  // semi-easy case: move track to left
        {
            tr_ = j;  // move track one right
        }
        else
        {
            ++a_[j];  // increment digit to the right
            j = 0;
            a_[j] = m1_[j];  // set far left digit = nine
            tr_ = j;  // move track to far left
        }

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { ::print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { ::print_mixedradix(bla, m1_, n_, false); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_SUBSET_LEXREV_H__
