#if !defined  HAVE_YOUNG_TAB_RGS_H__
#define       HAVE_YOUNG_TAB_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-young-tab-rgs.h"

#include "fxttypes.h"

//#include "jjassert.h"


class young_tab_rgs
// Restricted growth strings (RGS) for standard Young tableaux:
// the k-th occurrence of a digit d in the RGS must precede
// the k-th occurrence of the digit d+1.
// Generation in lexicographic order.
// Cf. OEIS sequences A000085 (all tableaux),
//   A001405 (tableaux with height <= 2, central binomial coefficients)
//   A001006 (tableaux with height <= 3, Motzkin numbers)
//   A005817 (height <= 4),  A049401 (height <= 5),  A007579 (height <= 6)
//   A007578 (height <= 7),  A007580 (height <= 8)
//   A001189 (height <= n-1),
//   A014495 (height = 2),  A217323 (height = 3),  A217324 (height = 4),
//   A217325 (height = 5),  A217326 (height = 6),  A217327 (height = 7),
//   A217328 (height = 8).
// Cf. OEIS sequences A061343 (all shifted tableaux; using condition is_shifted(1)):
// A210736 (height <= 2), A082395 (height <= 3).
{
public:
    ulong *a_;   // RGS
    ulong *st_;  // stats: st[j] is the number of occurrences of j in a[]
    // st[] contains a partition of n

    ulong n_;   // length of string
    ulong m_;   // number of allowed values for digits (== max height of tableaux)
    ulong h_;   // height: number of different digits used in a[] (==1 + max digit)

private:  // have pointer data
    young_tab_rgs(const young_tab_rgs&);  // forbidden
    young_tab_rgs & operator = (const young_tab_rgs&);  // forbidden

public:
    explicit young_tab_rgs(ulong n, ulong m=0)
    // Should have n >= 1 (for n==0 we take n=1).
    {
        n_ = (n ? n : 1);
        a_ = new ulong[n_];

        if ( m > n_ )  m = n_;  // avoid inefficiency (unreachable m)
        if ( m==0 )  m = n_;    // zero means all
        m_ = m;

//        st_ = new ulong[m_];
        st_ = new ulong[n_]; // excess elements for is_young_tab_rgs()

        first();
    }

    virtual ~young_tab_rgs()
    {
        delete [] a_;
        delete [] st_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<m_; ++k)  st_[k] = 0;
        st_[0] = n_;
        h_ = 1;
    }


private:

    bool try_incr(ulong j)
    // Increment a[j] if possible.
    // At entry st[1,2,...,m-1] must be valid for a[0,1,...,j].
    // At return st[1,2,...,m-1] is valid for a[0,1,...,j-1].
    {
        const ulong d = a_[j];
        const ulong st0 = st_[d] - 1;
        st_[d] = st0;  // (decremented) number of digits d

        h_ -= ( st0 == 0 );  // update height
        const ulong mm = h_ - ( m_ == h_ );

        for (ulong d1=d+1; d1<=mm; ++d1)  // optimized, scanning fewer candidates
        {
            ulong st1 = st_[d1] + 1; // (incremented) number of digits d

            if ( st1 <= st0 )  // can increment
            {
                a_[j] = d1;
                st_[d1] = st1;
                h_ += ( st1 == 1 );  // update height
                return true;
            }
        }

        // cannot increment, set digit to zero:
        a_[j] = 0;
        // do _not_ record zeros in suffix; done only at end of next()

        return false;
    }


public:

    ulong next()
    // Return leftmost changed index.
    // Return 0 if current string is last.
    {
        ulong j = n_;  // index of digit trying to increment
        ulong z = 0;   // count zeros filled in while trying to increment
        do
        {
            --j;
            if ( try_incr(j) )  break;
            ++z;  // we left a zero at a[j]

//            jjassert( is_young_tab_rgs(a_, j, st_, true) );

        }
        while ( j );

        st_[0] += z;  // now record zeros written

        if ( j==0 )  first();  // current is last

        return j;
    }


    const ulong * data()  const  { return a_; }


    ulong height()  const
    // Return height of tableaux (== 1 + largest digit used).
    {
        return h_;
    }

    ulong first_idx(ulong d)  const
    // Return index of first occurence of d.
    // n is returned if d is not a digit in the word a[].
    {
        for (ulong j=0; j<n_; ++j)
            if ( a_[j] == d )
                return j;

        return n_;
    }

    bool is_delayed(ulong s=1)  const
    // Return whether the first occurence of a digit d is
    // preceded by at least s+1 occurences of d-1.
    // Always true for s==0.
    {
        // fixme: inefficient
        const ulong h = height();
        for (ulong d=0; d<h; ++d)
        {
            ulong ct0 = 0, ct1 = 0;
            for (ulong k=0; k<n_; ++k)
            {
                ct0 += (a_[k]==d);
                ct1 += (a_[k]==d+1);
                if ( ct1 != 0 )
                    if ( (ct1 - ct0) < s )  return false;
            }
        }
        return true;
    }

    bool is_falling(ulong s=1)  const
    // Return whether falling multiplicities with difference at least s.
    // Same as: allowing only partitions into distinct parts (with diff>=s).
    // Always true for s==0.
    {
        const ulong md = height() - 1;
        for (ulong j=md; j>0; --j)
            if ( st_[j-1]-st_[j] < s )
                return false;

        return true;
    }

    bool is_shifted(ulong s=1)  const
    // Return whether still valid if row k is shifted to the right
    //  by s positions with respect to row k-1.
    // Always true for s==0.
    {
        if ( ! is_falling(s) )  return false;
        if ( ! is_delayed(s) )  return false;
        return true;
    }

    bool has_shape(const ulong *st, ulong h)
    {
        if ( h != h_ ) return false;
        for (ulong j=0; j<h; ++j)
            if ( st[j] != st_[j] )  return false;
        return true;
    }


    bool OK()  const
    { return  is_young_tab_rgs(a_, n_, st_, true); }


    void print_aa(ulong off=1)  const;  // ASCII art
};
// -------------------------


#endif  // !defined HAVE_YOUNG_TAB_RGS_H__
