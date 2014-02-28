#if !defined HAVE_KPERM_LEX_H__
#define      HAVE_KPERM_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

//#include "jjassert.h"
//#include "perm/permq.h"


class kperm_lex
// k-permutations of n elements in lexicographic order.
// Same as: k-prefixes of permutations of n elements.
// Same as: arrangements of k out of n elements.
{
public:
    ulong *p_;  // permutation
    ulong *ip_;  // inverse permutation
    ulong *d_;  // falling factorial number
    ulong n_;   // total number of elements
    ulong k_;   // permutations of k elements
    ulong u_;   // sort up to position u+1

private:  // have pointer data
    kperm_lex(const kperm_lex&);  // forbidden
    kperm_lex & operator = (const kperm_lex&);  // forbidden

public:
    explicit kperm_lex(ulong n)
    {
        n_ = n;
        k_ = n;
        p_ = new ulong[n_];
        ip_ = new ulong[n_];
        d_ = new ulong[n_+1];
        d_[0] = 0;  // sentinel
        ++d_;  // nota bene
        first(k_);
    }

    virtual ~kperm_lex()
    {
        delete [] p_;
        delete [] ip_;
        --d_;
        delete [] d_;
    }

    void first(ulong k)
    {
        k_ = k;
        u_ =  n_ - 1;
        if ( k_ < u_ )  u_ = k_;  // == min(k, n-1)

        for (ulong i=0; i<n_; i++)  p_[i] = i;
        for (ulong i=0; i<n_; i++)  ip_[i] = i;
        for (ulong i=0; i<n_; i++)  d_[i] = 0;
    }

    const ulong * data()  const  { return p_; }
    const ulong * invdata()  const  { return ip_; }

    bool next()
    {
        ulong i = k_ - 1;
        ulong m1 = n_ - i - 1;
        while ( d_[i] == m1 )  // increment mixed radix number
        {
            d_[i] = 0;
            ++m1;
            --i;
        }

        if ( (long)i < 0 )  return false;  // current is last

        ++d_[i];

        {  // find smallest element p[j] < p[i] that lies right of position i:
            ulong z = p_[i];
            do  { ++z; }  while ( ip_[z]<=i );
//            jjassert( z<n_ );
            const ulong j = ip_[z];
//            jjassert( j<n_ );

            swap2( p_[i], p_[j] );
            swap2( ip_[p_[i]], ip_[p_[j]] );
            ++i;
        }


        ulong z = 0;
        while ( i < u_ )
        {
            // find smallest element right of position i:
            while ( ip_[z] < i )  { ++z; }
//            jjassert( z<n_ );
            const ulong j = ip_[z];
//            jjassert( j<n_ );

            swap2( p_[i], p_[j] );
            swap2( ip_[p_[i]], ip_[p_[j]] );
            ++i;
        }

//        jjassert( is_inverse(p_, ip_, n_) );

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------



#endif  // !defined HAVE_KPERM_LEX_H__
