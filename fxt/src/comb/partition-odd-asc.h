#if !defined HAVE_PARTITION_ODD_ASC_H__
#define      HAVE_PARTITION_ODD_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "fxttypes.h"

//#include "jjassert.h"


class partition_odd_asc
// Integer partitions into odd parts.
// Representation as list of parts in non-decreasing order.
// Same as: compositions into non-decreasing odd parts.
// Lexicographic order.
// Cf. OEIS sequence A000009.
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition is into m parts

private:  // have pointer data
    partition_odd_asc(const partition_odd_asc&);  // forbidden
    partition_odd_asc & operator = (const partition_odd_asc&);  // forbidden

public:
    explicit partition_odd_asc(ulong n)
    {
        n_ = n;
        a_ = new ulong [n_+2];
        a_[0] = 0;  // sentinel solely for n==0
        ++a_;  // nota bene
        a_[0] = 0;  // sentinel to simplify detection of last partition
        first();
    }

    virtual ~partition_odd_asc()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ =  n_;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        const ulong z = a_[m_];   // can read sentinel a[0] if n==0
        const ulong y = a_[m_-1];  // can read sentinel a[0] (and a[-1] for n==0)
        ulong s = y + z;  // sum of parts we scan over

        ulong k;  // min value of next term
        if ( z >= y+4 )   // add last 2 terms
        {
            if ( m_ == 1 )  return 0;  // current is last

            k = y + 2;

            a_[m_-1] = k;
            s -= k;
        }
        else  // add last 3 terms
        {
            if ( m_ <= 2 )  return 0;  // current is last

            const ulong x = a_[m_-2];
            s += x;

            k = x + 2;
            m_ -= 2;
        }

//        jjassert( 1==(k&1) );
//        jjassert( 1==(s&1) );

        const ulong k2 = k + k;
        while ( s >= k2 + k )
        {
            a_[m_] = k;
            s -= k;
            m_ += 1;

            a_[m_] = k;
            s -= k;
            m_ += 1;
        }

//        jjassert( s!=0 );
        a_[m_] = s;

        return  m_;
    }


    bool OK()  const
    {
        if ( n_==0 )  return true;

        ulong s = 0;  // sum of parts == n  ?
        for (ulong j=1; j<=m_; ++j)  s += a_[j];
        if ( s!=n_ )  return false;

        for (ulong j=1; j<=m_; ++j)  // parts odd?
            if ( 0==(a_[j] & 1) )
                return false;

        for (ulong j=1; j<m_; ++j)  // parts non-decreasing?
            if ( a_[j] > a_[j+1] )
                return false;

        return true;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ODD_ASC_H__
