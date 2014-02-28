#if !defined HAVE_BINARY_SL_GRAY_H__
#define      HAVE_BINARY_SL_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"

// Cf. bits/bit-sl-gray.h for generation in a binary word.
// Cf. comb/subset-lex.h for subset-lex order.
// Cf. comb/mixedradix-subset-lex.h for subset-lex order for multisets.


class binary_sl_gray
// Binary numbers in a minimal-change order
// related so subset-lex order ("SL-Gray" order).
// Loopless generation, only O(1) data beyond the array of bits.
// Successive transitions are mostly adjacent,
// and otherwise have distance 3.
// Special case of class mixed_radix_sl_gray for base 2.
// Cf. OEIS sequence A217262.
{
public:
    ulong n_;   // number of digits
    ulong tr_;  // aux: current track (0 <= tr <= n)
    ulong dt_;  // aux: direction to which track tries to move
    ulong *a_;  // digits

    ulong j_;   // position of last change
    int dm_;    // direction of last change

private:  // have pointer data
    binary_sl_gray(const binary_sl_gray&);  // forbidden
    binary_sl_gray & operator = (const binary_sl_gray&);  // forbidden

public:
    explicit binary_sl_gray(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+2];  // all with sentinels

        a_[n_+1] = +1;  // != 0
        a_[0] = +1;

        ++a_;  // nota bene

        first();
    }

    virtual ~binary_sl_gray()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = 0;
        dt_ = +1;

        j_ = ( n_>=2 ? 1 : 0);  // wrt. last word
        dm_ = -1;  // wrt. last word
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;

        j_ = ( n_>=2 ? 1 : 0);  // wrt. first word
        dm_ = +1;  // wrt. first word

        if ( n_ >= 2 )
        {
            a_[1]  = 1;
            tr_ = 1;
            dt_ = -1UL;
        }
        else
        {
            a_[0]  = n_;  // zero for the empty set (for stopping condition)
            tr_ = 0;
            dt_ = +1;
        }
    }


    bool next()
    // Generate successor.
    // Return false if current was last.
    // Loopless algorithm.
    {
        if ( dt_ == +1 )  // try to append trailing ones
        {
            if ( a_[tr_] == 0 )  // can append  // may read sentinel a[n]
            {
                a_[tr_] = 1;
                j_ = tr_;
                dm_ = +1;
                ++tr_;
            }
            else
            {
                dt_ = -1UL;  // change direction
                tr_ = n_ - 1;
                j_ = tr_ - 1;
                if ( j_ > n_ )  return false;  // current is last (only for n_ <= 1)
                a_[j_] = ! a_[j_];
                dm_ = (a_[j_] ? +1 : -1);
            }
        }
        else  // dt_ == -1  // try to remove trailing ones
        {
            if ( a_[tr_-1] != 0 )   // can remove  // tr - 1 >= 0
            {
                a_[tr_] = 0;
                j_ = tr_;
                dm_ = -1;
                --tr_;
            }
            else
            {
                dt_ = +1;  // change direction
                j_ = tr_ - 2;
                if ( j_ > n_ )  return false;  // for (long)j < 0
                a_[j_] = ! a_[j_];
                dm_ = (a_[j_] ? +1 : -1);
                ++tr_;
            }
        }

        return true;
    }

    bool prev()
    // Generate predecessor.
    // Return false if current was first.
    // Loopless algorithm.
    {
        if ( dt_ != +1 )  // dt==-1  // try to append trailing ones
        {
            if ( a_[tr_+1] == 0 )  // can append  // may read sentinel a[n]
            {
                a_[tr_+1] = 1;
                j_ = tr_+1;
                dm_ = +1;
                ++tr_;
            }
            else
            {
                dt_ = +1;  // change direction
                tr_ = n_ - 1;
                j_ = tr_ - 1;
                a_[j_] = ! a_[j_];
                dm_ = (a_[j_] ? +1 : -1);
                ++tr_;
            }
        }
        else  // dt_ == +1  // try to remove trailing ones
        {
            if ( tr_ == 0 )
            {
                if ( a_[0]==0 )  return false;  // (only for n_ <= 1)
                a_[0] = 0;
                return true;
            }

            // tr - 1 >= -1 (can read low sentinel)
            if ( a_[tr_-2] != 0 )  // can remove
            {
                a_[tr_-1] = 0;
                j_ = tr_ - 1;
                dm_ = -1;
                --tr_;
            }
            else
            {
                dt_ = -1UL;  // change direction
                j_ = tr_ - 3;
                a_[j_] = ! a_[j_];
                dm_ = (a_[j_] ? +1 : -1);
                --tr_;
            }
        }

        return true;
    }


    ulong pos()  const  { return j_; }  // position of last change
    int dir()  const  { return dm_; }   // direction of last change


    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { ::print_mixedradix(bla, a_, n_, dfz); }
};
// -------------------------



#endif  // !defined HAVE_BINARY_SL_GRAY_H__
