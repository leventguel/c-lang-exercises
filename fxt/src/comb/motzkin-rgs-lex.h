#if !defined  HAVE_MOTZKIN_RGS_LEX_H__
#define       HAVE_MOTZKIN_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class motzkin_rgs_lex
// Motzkin restricted growth strings (RGS), lexicographic order.
// Cf. OEIS sequence A001006.
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
    ulong *s_;  // s[k]: how many consecutive increments up to position k
    ulong n_;   // number of digits

    ulong i_;  // at most i rises in a row, at most i+1 consecutive ones in the Dyck word
    // i==1 ==> Motzkin RGS
    // i==n ==> Catalan RGS

    char *str_;  // for bit string and paren string

private:  // have pointer data
    motzkin_rgs_lex(const motzkin_rgs_lex&);  // forbidden
    motzkin_rgs_lex & operator = (const motzkin_rgs_lex&);  // forbidden

public:
    explicit motzkin_rgs_lex(ulong n, ulong i=1)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
        i_ = i;

        a_ = new ulong[n_];
        s_ = new ulong[n_];

        str_ = new char[2*n_+1];
        str_[2*n_] = 0;

        first();
    }

    virtual ~motzkin_rgs_lex()
    {
        delete [] a_;
        delete [] s_;
        delete [] str_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
    }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_ - 1;
        ulong a0, a1;
        ulong s1;
        while ( j != 0 )
        {
            a1 = a_[j-1];
            a0 = a_[j];
            s1 = s_[j-1];

            if ( a0 < a1 )
            {
                a_[j] = a0 + 1;

                s_[j] = 0;
//                s_[j] = ( s1 ? s1 - 1 : 0 );  // still other strings for i!=1

                return j;
            }
            else
            {
                if ( a0 == a1 )
                {
#if 1  // default:
                    if ( s1 < i_ )
                    {
                        a_[j] = a0 + 1;
                        s_[j] = s1 + 1;
                        return j;
                    }
#else  // different from default for i!=1:
                    if ( 0==s_[j-1] )
                    {
                        a_[j] = a0 + 1;
                        s_[j] = i_;
                        return j;
                    }
#endif
                }
            }
            a_[j] = 0;
            s_[j] = 0;
            --j;
        }

        return 0;  // current is last
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


#endif  // !defined HAVE_MOTZKIN_RGS_LEX_H__
