#if !defined HAVE_PERM_INVOLUTION_H__
#define      HAVE_PERM_INVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

class perm_involution
// Involutions (self-inverse permutations).
// Cf. OEIS sequence A000085.
{
public:
    ulong *p_;  // self-inverse permutation in 0, 1, ..., n-1
    ulong n_;   // number of elements to permute

private:  // have pointer data
    perm_involution(const perm_involution&);  // forbidden
    perm_involution & operator = (const perm_involution&);  // forbidden

public:
    explicit perm_involution(ulong n)
    {
        n_ = n;
        p_ = new ulong[n_];
        first();
    }

    virtual ~perm_involution()  { delete [] p_; }

    void first()  { for (ulong i=0; i<n_; i++)  p_[i] = i; }

    const ulong * data()  const  { return p_; }

    bool next()
    {
        for (ulong j=n_-1; j!=0; --j)
        {
            ulong ip = p_[j];   // inverse perm == perm
            p_[j] = j;  p_[ip] = ip;  // undo prior swap

            while ( (long)(--ip) >= 0 )
            {
                if ( p_[ip]==ip )
                {
                    p_[j] = ip;  p_[ip] = j;  // swap2(p_[j], p_[ip] );
                    return true;
                }
            }
        }
        return false;  // current permutation is last
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_INVOLUTION_H__

