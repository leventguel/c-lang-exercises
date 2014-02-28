#if !defined HAVE_PARTITION_ASC_SORTS2_PP_H__
#define      HAVE_PARTITION_ASC_SORTS2_PP_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/print-composition-by-sorts.h"

#include "fxtio.h"

#include "fxttypes.h"


//#define PARTITION_ASC_SORTS2_PP_FIXARRAYS  // default off


class partition_asc_sorts2_pp
// Partitions into parts of s[k] sorts for part (size) k.
// Representation as non-decreasing lists.
// Lexicographic order: major order by parts, minor by sorts.
// Cf. OEIS sequence A000219 (planar partitions).
// Cf. OEIS sequences (partitions of n into parts of s kinds):
// A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
// A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).
{
public:
#ifndef PARTITION_ASC_SORTS2_PP_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;  // sorts of parts, 0 <= s_[j] <= ns1
    ulong *ns1_;  // ns1[j] is sort of part a[j]
#else
    ulong a_[448];  // > 2^66 partitions of 1 sort
    ulong s_[448];
    ulong ns1_[448];  // number of sorts - 1 for each part size
#endif
    ulong n_;   // partition of n
    ulong m_;   // current partition is into m parts

private:  // have pointer data
    partition_asc_sorts2_pp(const partition_asc_sorts2_pp&);  // forbidden
    partition_asc_sorts2_pp & operator = (const partition_asc_sorts2_pp&);  // forbidden

public:
    explicit partition_asc_sorts2_pp(ulong n, ulong ns, const ulong *vns=0)
    // Should have: ns >= 1.
    {
        n_ = n;
#ifndef PARTITION_ASC_SORTS2_PP_FIXARRAYS
        a_ = new ulong [n_+1+(n_==0)];
        s_ = new ulong [n_+1+(n_==0)];
        ns1_ = new ulong [n_+1+(n_==0)];
#endif
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        s_[0] = 0;  // returned by last_sort() when n==0
        s_[1] = 0;  // returned by first_sort() when n==0
        ns1_[0] = 0;

        if ( vns )  // number of sorts given for all parts
        {
            for (ulong k=0; k<n; ++k)
                ns1_[k+1] = (vns[k] ? vns[k] - 1 : 0);  // avoid 'no sorts'
        }
        else
        {
            if ( ns==0 )  // k sorts of part (size) k
                for (ulong k=1; k<=n; ++k)  ns1_[k] = k - 1;
            else // use ns as radix for all digits:
                for (ulong k=1; k<=n; ++k)  ns1_[k] = ns - 1;
        }

        first();
    }

    virtual ~partition_asc_sorts2_pp()
    {
#ifndef PARTITION_ASC_SORTS2_PP_FIXARRAYS
        delete [] a_;
        delete [] s_;
        delete [] ns1_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }
    const ulong * sdata()  const  { return  s_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong first_sort()  const  { return s_[1]; }
    ulong last_sort()  const  { return s_[m_]; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        for (ulong k=1; k<=n_; ++k)  s_[k] = 0;
        m_ = n_;
    }

//    void last()
//    {
//        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
//        a_[1] = n_;
//        for (ulong k=1; k<=n_; ++k)  s_[k] = 0;
//        s_[1] = ns1_[1];
//        m_ = 1;
//    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        const ulong z = a_[m_];

        if ( s_[m_] != ns1_[z] )  // a[m] is not last sort
        {
            s_[m_] += 1;  // next sort for current end
            return  m_;
        }

        // else:  a[m] is last sort
        if ( a_[m_] == n_ )  return 0;  // current is last

        const ulong w = a_[m_-1];
        if ( s_[m_-1] != ns1_[w] )  // previous part not last sort
        {
            const ulong s1 = s_[m_-1] + 1;
            s_[m_-1] = s1;  // next sort of previous part

            ulong y = a_[m_];
            const ulong x = a_[m_-1];
            while ( x <= y )
            {
                a_[m_] = x;
                s_[m_] = s1;
                y -= x;
                m_ += 1;
            }

            m_ -= 1;
            a_[m_] = x + y;

            if ( a_[m_] == x )  s_[m_] = s1;
            else                s_[m_] = 0;

            return  m_;
        }
        else  // previous part is last sort
        {
            ulong y = a_[m_] - 1;
            m_ -= 1;
            const ulong x = a_[m_] + 1;
            while ( x <= y )
            {
                a_[m_] = x;
                s_[m_] = 0;
                y -= x;
                m_ += 1;
            }
            a_[m_] = x + y;
            s_[m_] = 0;

            return  m_;
        }
    }

private:
    bool sorts_in_runs_sorted(bool aq=true)  const
    // Return whether for all runs of equal parts
    // the sorts of parts are monotone.
    // By default test for ascending order (aq==true),
    // otherwise for decreasing order.
    {
        const ulong *A = data();
        const ulong *S = sdata();
        ulong j = 0, aj = A[j], sj=S[j];
        while ( j < m_ )
        {
            if ( A[j] == aj )
            {
                if ( aq )
                { if ( S[j] < sj )  return false; }
                else
                { if ( S[j] > sj )  return false; }
            }
            else
            {
                aj = A[j];
            }
            sj = S[j];
            ++j;
        }
        return true;
    }

public:
    bool OK()  const
    {
        if ( n_ == 0 )  return true;

        ulong s = 0;  // check that sum is n
        for (ulong j=1; j<=m_; ++j)  s += a_[j];
        if ( s != n_ )  return false;

        for (ulong j=1; j<=m_; ++j)  // valid sorts?
            if ( s_[j] > ns1_[a_[j]] )  return false;

        if ( ! sorts_in_runs_sorted() )  return false;

        return true;
    }

    void print(const char *bla)  const
    {
        if ( bla )  cout << bla;

        cout << "[";
        for (ulong j=1; j<=m_; ++j)
        {
            cout << setw(2) << a_[j];
            cout << ":" << s_[j];
            cout << " ";
        }
        cout << " ]";
    }

    void print_by_sorts(const char *bla)  const
    {
        if ( bla )  cout << bla;
        print_composition_by_sorts( data(), sdata(), num_parts() );
    }

//    void print_aa()  const  // ASCII art
//    { ::print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_SORTS2_PP_H__
