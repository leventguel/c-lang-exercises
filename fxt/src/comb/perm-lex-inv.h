#if !defined  HAVE_PERM_LEX_INV_H__
#define       HAVE_PERM_LEX_INV_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


#define PERM_LEX_INV_FIXARRAYS  // use arrays instead of pointers (speedup)

#define PERM_LEX_INV_OPT  // define to use easy case optimization (speedup)


class perm_lex_inv
// Permutations in lexicographic order, with inverse permutations.
// Generation via rising factorial numbers.
{
public:
#ifndef PERM_LEX_INV_FIXARRAYS
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ...]
    ulong *x_;  // permutation
    ulong *xi_;  // inverse permutation
#else
    ulong d_[32];
    ulong x_[32];
    ulong xi_[32];
#endif
    ulong n_;   // permutations of n elements

private:  // have pointer data
    perm_lex_inv(const perm_lex_inv&);  // forbidden
    perm_lex_inv & operator = (const perm_lex_inv&);  // forbidden

public:
    explicit perm_lex_inv(ulong n)
    {
        n_ = n;
#ifndef PERM_LEX_INV_FIXARRAYS
        const ulong zq = ( n_ >= 2 ? n_ : 2 );  // make things work for n==1
        d_ = new ulong[n_ + zq];
        x_ = new ulong[n_ + zq];
        xi_ = new ulong[n_ + zq];
#endif
        if ( n>=2 )  d_[n-1] = 0;  // sentinel
        else
        {
            d_[0] = 1;  d_[1] = 0;
            x_[0] = 0;  x_[1] = 0;
            xi_[0] = 0;  xi_[1] = 0;
        }
        first();
    }

    virtual ~perm_lex_inv()
    {
#ifndef PERM_LEX_INV_FIXARRAYS
        delete [] d_;
        delete [] x_;
        delete [] xi_;
#endif
    }

private:
    void swap(ulong i1, ulong i2)
    {
        const ulong x1 = x_[i1], x2 = x_[i2];
        x_[i2] = x1;   x_[i1] = x2;
        xi_[x1] = i2;  xi_[x2] = i1;
    }

public:
    const ulong * data()  const  { return x_; }
    const ulong * invdata()  const  { return xi_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  x_[k] = k;
        for (ulong k=0; k<n_; ++k)  xi_[k] = k;
//        for (ulong k=0; k<n_; ++k)  x_[k] = n_-1-k;  // ==> reversed order
//        for (ulong k=0; k<n_; ++k)  xi_[k] = n_-1-k;  // ==> reversed order

        if ( n_!= 0 )  // make things work for n==0
            for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
    }

    bool next()
    {
#ifdef PERM_LEX_INV_OPT
        if ( d_[0]==0 )  // easy case
        {
            d_[0] = 1;
//            swap2(x_[n_-1], x_[n_-2]);
            swap(n_-1, n_-2);
            return true;
        }
        else
        {
            d_[0] = 0;
            ulong j = 1;
            ulong m1 = 2;  // nine in falling factorial base
#else  // PERM_LEX_INV_OPT

            ulong j = 0;
            ulong m1 = 1;  // nine in falling factorial base
#endif  // PERM_LEX_INV_OPT
            while ( d_[j]==m1 )
            {
                d_[j] = 0;
                ++m1;
                ++j;
            }

            // check whether current permutation is last:
//            if ( j==n_-1 )  return false;  // OK for n>=2
            if ( j+1>=n_ )  return false;  // OK for n>=0

            ulong dj = d_[j];
            d_[j] = dj + 1;

//            swap2( x_[n_-1-dj], x_[n_-j-2] );
            swap( n_-1-dj, n_-j-2 );

            {  // reverse range [n-1-j...n-1]:
                ulong a = n_-1-j,  b = n_-1;
                while ( a<b )
                {
//                    swap2(x_[a], x_[b]);
                    swap(a, b);
                    --b;
                    ++a;
                }
            }

            return true;
#ifdef PERM_LEX_INV_OPT
        }
#endif
    }

public:
    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }
};
// -------------------------

//#undef PERM_LEX_INV_FIXARRAYS  // better leave in
//#undef PERM_LEX_INV_OPT  // better leave in


#endif  // !defined HAVE_PERM_LEX_INV_H__
