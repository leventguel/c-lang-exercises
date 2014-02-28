#if !defined  HAVE_DYCK_RGS_H__
#define       HAVE_DYCK_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "comb/comb-print.h"

// Whether to use arrays instead of pointers:
//#define DYCK_RGS_FIXARRAYS  // small speedup


class dyck_rgs
// Restricted growth strings (RGS) corresponding to k-ary Dyck words (k=i+1):
//  s[0,...,n-1] such that s[k] <= s[k-1]+i
// Lexicographic order.
// Number of RGS is binomial(i*n,n)/((i-1)*n+1), (Catalan numbers for i=1).
{
public:
#ifndef DYCK_RGS_FIXARRAYS
    ulong *s_;  // restricted growth string
#else
    ulong s_[128];  // restricted growth string
#endif
    ulong n_;   // Length of strings
    ulong i_;   // s[k] <= s[k-1]+i
    // i==1 ==> RGS for strings for valid parenthesis strings

private:  // have pointer data
    dyck_rgs(const dyck_rgs&);  // forbidden
    dyck_rgs & operator = (const dyck_rgs&);  // forbidden

public:
    explicit dyck_rgs(ulong n, ulong i=1)
    {
        n_ = (n > 0 ? n : 1 );  // do not fail for n==0
        i_ = i;
#ifndef DYCK_RGS_FIXARRAYS
        s_ = new ulong[n_];
#endif
        first();
    }

    virtual ~dyck_rgs()
    {
#ifndef DYCK_RGS_FIXARRAYS
        delete [] s_;
#endif
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = i_ * k;
    }

    ulong next()
    // Return index of first changed element in s[],
    // return zero if current string is the last.
    {
#if 1
        ulong k = n_;

    start:
        --k;
        if ( k==0 )  return 0;

        ulong sk = s_[k] + 1;
        ulong mp = s_[k-1] + i_;
        if ( sk > mp )  // "carry"
        {
            s_[k] = 0;
            goto start;
        }

        s_[k] = sk;
        return k;

#else  // same speed:
        ulong k = n_;
        while ( --k )
        {
            ulong sk = s_[k] + 1;
            ulong mp = s_[k-1] + i_;
            if ( sk <= mp )  // can we increment?
            {
                s_[k] = sk;
                return k;
            }
            s_[k] = 0;
        }
        return 0;
#endif
    }

    ulong prev()
    // Return index of first changed element in s[],
    // return zero if current string is the first.
    {
        ulong k = n_;
        while ( --k )
        {
            if ( s_[k] != 0 )  // can we decrement?
            {
                --s_[k];
                for (ulong j=k+1; j<n_; ++j)  s_[j] = s_[j-1] + i_;
                return k;
            }
            s_[k] = 0;
        }
        return 0;
    }


    const ulong* data()  const  { return s_; }

    void print(const char *bla=0, bool dfz=true)  const
    { ::print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_DYCK_RGS_H__
