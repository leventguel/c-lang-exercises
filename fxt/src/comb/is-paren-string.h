#if !defined  HAVE_IS_PAREN_STRING_H__
#define       HAVE_IS_PAREN_STRING_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline bool is_paren_string(const Type *str, ulong n2)
// Return whether parenthesis string is valid.
// Works for any pair of symbols.
{
    if ( n2==0 )  return true;  // nothing to do
    const Type c1 = str[0];
    long s = 0;  // running sum
    for (ulong js=0; js<n2; ++js)
    {
        if ( str[js] == c1 )
        {
            ++s;
        }
        else
        {
            --s;
            if ( s<0 )  return false;
        }
    }
    return (s==0);
}
// -------------------------

#endif  // !defined HAVE_IS_PAREN_STRING_H__
