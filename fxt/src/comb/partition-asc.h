#if !defined HAVE_PARTITION_ASC_H__
#define      HAVE_PARTITION_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "comb/partition-print-aa.h"

#include "fxttypes.h"


//#define PARTITION_ASC_FIXARRAYS  // default off
// small speedup with gcc 4.5.0, slowdown with gcc 4.8.0


class partition_asc
// Integer partitions.
// Representation as list of parts in non-decreasing order.
// Same as: compositions into non-decreasing parts.
// Lexicographic order.
// Cf. OEIS sequence A000041.
{
public:
#ifndef PARTITION_ASC_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions
#endif

    ulong n_;  // integer partitions of n
    ulong m_;  // current partition is into m parts

private:  // have pointer data
    partition_asc(const partition_asc&);  // forbidden
    partition_asc & operator = (const partition_asc&);  // forbidden

public:
    explicit partition_asc(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ASC_FIXARRAYS
        a_ = new ulong [n_+1];
#endif
        first();
    }

    virtual ~partition_asc()
    {
#ifndef PARTITION_ASC_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current partition is the last.
    {
        // Based on
        //   Jerome Kelleher, Barry O'Sullivan:
        //   Generating All Partitions: A Comparison Of Two Encodings,
        //   arXiv:0909.2331v1 [cs.DS], (12-September-2009).

        if ( m_ <= 1 )  return 0;  // current is last

        // [*, Y, Z] --> [*, Y+1, Y+1, ..., Y+1, W]
        // with at least one occurrence of Y+1, and Y+1 <= W < 2*(Y+1)

        ulong z1 = a_[m_] - 1;  // take one unit from last part
        m_ -= 1;
        const ulong y1 = a_[m_] + 1;  // add one unit to previous part

        while ( y1 <= z1 )  // can put part Y+1
        {
            a_[m_] = y1;
            z1 -= y1;
            m_ += 1;
        }
        a_[m_] = y1 + z1;

        return  m_;
    }

    ulong durfee_n()  const
    // Return side length of the Durfee square.
    {
        ulong d = 0;
        for (ulong j=m_, s=1;  j>=1;  --j, ++s)
        {
            if ( a_[j] >= s )  ++d;
            else  break;
        }
        return d;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_aa()  const  // ASCII art
    { ::print_partition_asc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { ::print_partition_asc_conj_aa(data(), m_); }

    bool OK()  const
    {
        ulong s = 0;
        for (ulong j=1; j<=m_; ++j)  s += a_[j];
        if ( s != n_ )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_H__
