#if !defined  HAVE_DYCK_RGS_SUBSET_LEX_H__
#define       HAVE_DYCK_RGS_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// Cf. comb/catalan-subset-lex.h for Catalan RGS in subset-lex order.


#define DYCK_RGS_SUBSET_LEX_SC  // whether to allow n<=1
// this gives a small slowdown

class dyck_rgs_subset_lex
// Restricted growth strings (RGS) for k-ary Dyck words, subset-lex order.
{
public:
    ulong *as_;  // digits of the RGS: as_[k] <= as[k-1] + 1
    ulong tr_;  // current track
    ulong n_;   // Number of digits in RGS
    ulong i_;   // k-ary Dyck words: i = k - 1
    char *str_;  // Dyck word

private:  // have pointer data
    dyck_rgs_subset_lex(const dyck_rgs_subset_lex&);  // forbidden
    dyck_rgs_subset_lex & operator = (const dyck_rgs_subset_lex&);  // forbidden

public:
    explicit dyck_rgs_subset_lex(ulong n, ulong k)
    // Must have k>=2
    {
        n_ = n;
        i_ = k - 1;

        as_ = new ulong[n_+ 1 + (n_==0)];  // incl. sentinel
        as_[0] = +1;  // sentinel !=0  to catch scan to the left
        ++as_;  // nota bene
        if ( n_==0 )  as_[0] = 0;

        str_ = new char[k*n_+1];  str_[k*n_] = 0;

        first();
    }

    virtual ~dyck_rgs_subset_lex()
    {
        --as_;
        delete [] as_;
        delete [] str_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  as_[k] = 0;
        tr_ = 1;

        // make things work for n <= 1:
        if ( n_ <= 1 )  tr_ = 0;
    }

    bool next()
    {
        ulong j = tr_;
        if ( as_[j] < as_[j-1] + i_ )   // easy case 1: can increment track
        {
#ifdef DYCK_RGS_SUBSET_LEX_SC
            if ( n_ <= 1 )  return false;
#endif
            ++as_[j];
            return true;
        }

        const ulong j1 = j + 1;
        if ( j1 < n_ )  // easy case 2: can attach
        {
            as_[j1] = +1;
            tr_ = j1;
            return true;
        }

        as_[j] = 0;

        // Find nonzero track to the left:
        do  { --j; }  while ( as_[j] == 0 );  // can read sentinel

        if ( (long)j < 0 )  return false;  // current is last

        --as_[j];
        ++j;
        as_[j] = 1;
        tr_ = j;
        return true;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  as_[k] = 0;
        tr_ = n_ - 1;
        // make things work for n <= 1:
        if ( n_==0 )
        {
            tr_ = 0;
            as_[0] = 1;
        }
        if ( n_>=2 )  as_[tr_] = i_;
    }


    bool prev()
    // Loopless algorithm.
    {
#ifdef DYCK_RGS_SUBSET_LEX_SC
        if ( n_<=1 )  return false;
#endif

        ulong j = tr_;
        if ( as_[j] > 1 )   // easy case 1: can decrement track
        {
            --as_[j];
            return true;
        }

        const ulong aj = as_[j];  // zeor or one
        as_[j] = 0;
        --j;
        if ( as_[j] == as_[j-1] + i_ )  // move track to the left
        {
            --tr_;
            return true;
        }

        if ( j==0 )  // current or next is last
        {
            if ( aj == 0 )  return false;
            return true;
        }

        ++as_[j];
        tr_ = n_ - 1;
        as_[tr_] = as_[tr_-1] + i_;
        return true;
    }

    const ulong *data()  const  { return as_; }

    const char* bit_string()
    {
        const ulong k = i_ + 1;
        for (ulong j=0; j<k*n_; ++j)  str_[j] = '.';
        for (ulong j=0; j<n_; ++j)  str_[j*k - as_[j]] = '1';
        return str_;
    }
};
// -------------------------

#endif  // !defined HAVE_DYCK_RGS_SUBSET_LEX_H__
