#if !defined  HAVE_CATALAN_RGS_H__
#define       HAVE_CATALAN_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// whether to use arrays instead of pointers:
//#define CATALAN_RGS_FIXARRAYS  // default is off

class catalan_rgs
// Catalan restricted growth strings (RGS), lexicographic order.
// The number of length-n RGS is (OEIS sequence A000108)
//  1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, ...
{
public:
#ifndef CATALAN_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
#else
    ulong a_[64];
#endif
    ulong n_;   // Number of digits (paren pairs)

    char *str_;  // paren string

private:  // have pointer data
    catalan_rgs(const catalan_rgs&);  // forbidden
    catalan_rgs & operator = (const catalan_rgs&);  // forbidden

public:
    explicit catalan_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
#ifndef CATALAN_RGS_FIXARRAYS
        a_ = new ulong[n_];
#endif
        str_ = new char[2*n_+1];
        str_[2*n_] = 0;

        first();
    }

    virtual ~catalan_rgs()
    {
#ifndef CATALAN_RGS_FIXARRAYS
        delete [] a_;
#endif
        delete [] str_;
    }

    void first()
    { for (ulong k=0; k<n_; ++k)  a_[k] = 0; }

    void last()
    { for (ulong k=0; k<n_; ++k)  a_[k] = k; }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_ - 1;
        while ( j != 0 )
        {
            if ( a_[j] <= a_[j-1] )  break;
            a_[j] = 0;
            --j;
        }

        if ( j==0 )  return 0;  // current is last

        ++a_[j];
        return j;
    }


    ulong prev()
    // Return position of leftmost change, zero with first.
    {
        ulong j = n_ - 1;
        while ( j != 0 )
        {
            if ( a_[j] != 0 )  break;
            --j;
        }

        if ( j==0 )  return 0;  // current is first

        --a_[j];
        ulong i = j;
        while ( ++i < n_ )  a_[i] = a_[i-1] + 1;
        return j;
    }


    const ulong *data()  const  { return a_; }

    const char* bit_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = '.';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a_[k] ] = '1';
        return str_;
    }

    const char* paren_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = ')';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a_[k] ] = '(';
        return str_;
    }
};
// -------------------------


#endif  // !defined HAVE_CATALAN_RGS_H__
