#if !defined HAVE_MIXEDRADIX_SL_GRAY_H__
#define      HAVE_MIXEDRADIX_SL_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_sl_gray
// Mixed radix numbers in a minimal-change order
// related so subset-lex order ("SL-Gray" order).
{
public:
    ulong n_;   // Number of digits (n kinds of elements in multiset, n>=1)
    ulong tr_;  // aux: current track
    ulong *a_;  // digits of mixed radix number (multiplicity of kind k in subset).
    ulong *d_;  // directions
    ulong *m1_;  // nines (radix minus one) for each digit (multiplicity of kind k in set).

    ulong j_;   // position of last change
    int dm_;    // direction of last change

private:  // have pointer data
    mixedradix_sl_gray(const mixedradix_sl_gray&);  // forbidden
    mixedradix_sl_gray & operator = (const mixedradix_sl_gray&);  // forbidden

public:
    explicit mixedradix_sl_gray(ulong n, ulong mm, const ulong *m=0)
    // Must have n>=1
    {
        n_ = n;
        a_ = new ulong[n_+2];  // all with sentinels
        d_ = new ulong[n_+2];
        m1_ = new ulong[n_+2];

        a_[n_+1] = +1;  // != 0
        m1_[n_+1] = +1;  // same as a_[n+1]
        d_[n_+1] = +1;   // positive

        a_[0] = +2;  // >=+2
        m1_[0] = +2;  //  same as a_[0]
        d_[0] = 0;  // zero

        ++a_; ++d_; ++m1_;  // nota bene

        mixedradix_init(n_, mm, m, m1_);
        first();
    }

    virtual ~mixedradix_sl_gray()
    {
        --a_;  --d_;  --m1_;
        delete [] a_;
        delete [] d_;
        delete [] m1_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  d_[k] = +1;
        tr_ = 0;

        j_ = 0;  // arbitrary
        dm_ = -1;  // arbitrary
    }

//    void last()
//    {
//    }


    bool next()
    // Generate next.
    // Return false if current was last.
    // Loopless if all radices are even because all successive changes
    // are at a distance of at most 2 (two-close Gray code).
    {
        ulong j = tr_;
        const ulong dj = d_[j];
        const ulong ij = a_[j] + dj;

//        if ( (ij != 0) && (ij <= m1_[j]) )  // easy case
//        if ( (ij != 0) & (ij <= m1_[j]) )  // easy case
        if ( ij - 1 < m1_[j] )  // easy case
        {
            a_[j] = ij;
            j_ = j;
            dm_ = (int)dj;
            return true;
        }

        d_[j] = -dj;

        if ( dj == +1 )  // so a_[j] == m1_[j] == nine
        {
            // Try to move track right with a[j] == nine:
            const ulong j1 = j + 1;
            if ( a_[j1] == 0 )  // can read high sentinel
            {
                a_[j1] = +1;
                tr_ = j1;
                j_ = j1;
                dm_ = +1;
                return true;
            }
        }
        else  // here dj == -1, so a_[j] == 1
        {
            if ( (long)j <= 0 )  return false;  // current is last

            // Try to move track left with a[j] == 1:
            const ulong j1 = j - 1;
            if ( a_[j1] == m1_[j1] )  // can read low sentinel when n_ == 1
            {
                a_[j] = 0;
                d_[j1] = -1UL;
                tr_ = j1;
                j_ = j1;
                dm_ = -1;
                return true;
            }
        }


        // find first changeable track to the left:
        --j;
        while ( a_[j] + d_[j] > m1_[j] )  // may read low sentinels
        {
            d_[j] = -d_[j];
            --j;
        }

        if ( (long)j < 0 )  return false;  // current is last

        // Change digit left but keep track:
        a_[j] += d_[j];

        j_ = j;
        dm_ = (int)d_[j];

        return true;
    }

//    bool prev()
//    // Generate previous.
//    // Return false if current was first.
//    {  // Same as next() but direction d[] negated
//    }

    ulong pos()  const  { return j_; }  // position of last change
    int dir()  const  { return dm_; }   // direction of last change


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



#endif  // !defined HAVE_MIXEDRADIX_SL_GRAY_H__
