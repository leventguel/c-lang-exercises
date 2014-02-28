#if !defined HAVE_PARTITION_2FALL_DESC_H__
#define      HAVE_PARTITION_2FALL_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "comb/partition-print-aa.h"

#include "fxttypes.h"

//#include "fxtio.h"
//#include "jjassert.h"


class partition_2fall_desc
// Partitions of n is a partition a[1] + a[2] + ... + a[m] = n
//   such that 2*a[k] <= a[k-1].
// Representation as non-increasing list of parts.
// Lexicographic order.
// Cf. OEIS sequence A000929.
{
public:
    ulong n_;   // non-squashing integer partition of n
    ulong m_;   // current partition is into m parts
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_2fall_desc(const partition_2fall_desc&);  // forbidden
    partition_2fall_desc & operator = (const partition_2fall_desc&);  // forbidden


private:
    ulong mers_t(ulong s)
    // Return greatest t such that 2^t-1 <= s.
    {
        ulong t = 0;
        ulong b = 1;
        while ( s+1 > b )  { ++t;  b <<= 1; }

        if ( s < b-1 )  { --t;  b >>= 1; }

        return t;
    }

    ulong write_tail(ulong s, ulong j)
    // Write lexicographically first partition of s, starting at index j.
    // Return last index written to.
    // Undefined for s == 0.
    {
        ulong h = mers_t(s);
        ulong t = j + h - 1;  // return value
        ulong b = 1UL << h;
        s -= (b-1);
        b >>= 1;
        for (ulong i=j; b!=0;  ++i, b>>=1)  a_[i] = b;  // write

        while ( s != 0 )
        {
#if 1
            if ( s<=2 )
            {
                a_[j] += s;
                return t;
            }
#endif
            h = mers_t(s);
            b = 1UL << h;
            s -= (b-1);
            b >>= 1;
            for (ulong i=j; b!=0;  ++i, b>>=1)  a_[i] += b;  // add
        }

        return t;
    }


public:
    explicit partition_2fall_desc(ulong n)
    {
        n_ = n;
        ulong k = 1;
        if ( n_ != 0 )  k += mers_t(n_);
        a_ = new ulong [k];
        first();
    }

    virtual ~partition_2fall_desc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = 2*n_;  // read-only
        m_ = 0;
        if ( n_!=0 )  m_ = write_tail(n_, 1);
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong j = m_;
        ulong s = a_[j];

        ulong y = a_[j-1];
        ulong x = a_[j-2];  // can read sentinel a[0]

        --j;
        while ( 2*(y+1) > x  )  // search for y we can inrease
        {
            s += y;
            y = x;
            --j;
            x = a_[j-1];  // can read sentinel a[0]
        }

        a_[j] = y + 1;
        s += 0 - 1;

        if ( s == 0 )
        {
            --m_;
            return m_;
        }

        m_ = write_tail(s, j+1);
        return m_;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_aa()  const  // ASCII art
    { ::print_partition_desc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { ::print_partition_desc_conj_aa(data(), m_); }


    bool OK()  const
    {
        if ( m_ > n_ )  return false;

        ulong s = 0;  // sum OK ?
        for (ulong j=1; j<=m_; ++j)  s += a_[j];
        if ( s != n_ )  return false;

        for (ulong j=2; j<=m_; ++j)  // descending?
            if ( a_[j-1] < a_[j] )  return false;

        for (ulong j=2; j<=m_; ++j)  // 2*a[j] <= a[j-1] ?
            if ( 2*a_[j] > a_[j-1] )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_2FALL_DESC_H__
