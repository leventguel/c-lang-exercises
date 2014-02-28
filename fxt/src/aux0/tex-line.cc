// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/tex-line.h"  // define TEX_USE_PICT2E

#include "fxtio.h"  // setprecision()
#include "fxttypes.h"

#include "jjassert.h"  // jjnote: asserts used in code: TeX-line

#include <cmath>  // sqrt(), fabs(), round()



void
tex_line(long x0, long y0, long x1, long y1, bool vq/*=true*/)
// Print TeX command to draw vector (or line)
//   from (x0, y0) to (x1, y1).
// For \line(dx, dy){length} and \vector(dx, dy}{length}
// Note: For \line(dx, dy){length} and \vector(dx, dy}{length}
// the argument 'length' is the VERTICAL coordinate for
// vertical line segments, else the HORIZONTAL coordinate.
{
#ifdef TEX_USE_PICT2E

    double dx = (double)(x1 - x0);
    double dy = (double)(y1 - y0);

    // length:
    double len = sqrt( dx*dx + dy*dy );
//    cout << "%% " << len << endl;

    // slopes:
    long sx = (long)round( 999.0 * dx/len );
    long sy = (long)round( 999.0 * dy/len );
    // simplify for purely horiz/vert case:
    if ( sx==0 )  sy = 1;
    if ( sy==0 )  sx = 1;

    // "length" to be used with \vector:
    double vlen = fabs( dx );
    if ( vlen < 1e-4 )  vlen = round(len);

    cout << "\\put(" << x0 << "," << y0 << ")";
    if ( vq )  cout << "{\\vector(";
    else       cout << "{\\line(";
    cout << sx << "," << sy << ")"
         << "{" << setprecision(3) << vlen << "}}"
         << endl;

#else  // TEX_USE_PICT2E

    cout << "\\curve("
         << x0 << "," << y0 << ", "
         << x1 << "," << y1 << ")"
         << endl;

#endif  // TEX_USE_PICT2E
}
// -------------------------


static inline double chop0(double x)  { if ( fabs(x)<0.001 )  x=0.0;  return x; }

void
tex_line_fl(double x0, double y0, double x1, double y1, bool vq/*=true*/)
// Print TeX command to draw vector (or line)
//   from (x0, y0) to (x1, y1).
// Note: For \line(dx, dy){length} and \vector(dx, dy}{length}
// the argument 'length' is the VERTICAL coordinate for
// vertical line segments, else the HORIZONTAL coordinate.
{
//    cerr << "P0=(" << x0 << ", " << y0 <<  ")"
//         << "   "
//         << "P1=(" << x1 << ", " << y1 <<  ")"
//         << endl;

    double dx = x1 - x0,  dy = y1 - y0;

    // length:
    double len = sqrt( dx*dx + dy*dy );

//    jjassert( len > 0.001 );
    if ( len < 0.001 )  return;  // draw nothing

    // slopes:
    long sx = (long)round( 99.0 * dx/len );
    long sy = (long)round( 99.0 * dy/len );
    // simplify for purely horiz/vert case:
//    if ( sx==0 )  sy = 1;
//    if ( sy==0 )  sx = 1;

    // "length" to be used with \vector or \line:
    double vlen = fabs( dx );
//    if ( fabs(vlen)<1e-4 )  vlen = 1;
//    if ( vlen < 1e-4 )  vlen = round(len);
    if ( vlen < 1e-4 )  vlen = chop0(len);

    x0 = chop0(x0);
    y0 = chop0(y0);

    cout << "\\put(" << x0 << "," << y0 << ")";
    if ( vq )  cout << "{\\vector(";
    else       cout << "{\\line(";
    cout << sx << "," << sy << ")"
         << "{" << vlen << "}}"
         << endl;
}
// -------------------------


void
tex_draw_turn(double x, double y,
              double dx, double dy,
              double ndx, double ndy,
              ulong style,
              bool vq/*=true*/)
// Draw the part of the turn from
// (x, y) over (x+dx, y+dy) to  (x+ndx, y+ndy)
// indicated as X1, X2, X3 below.
//                                     :
//           NX == X + DX              :
//          /  \                       :
//         * X2 * X3                   :
//        /      \                     :
//       * X1     \                    :
//    X /          \ == NX + NDX       :
//
//.
// (Colons to avoid warning about multi-line comment.)
{
    cout.precision(4);
    double nx = x + dx,  ny = y + dy;  // next (x, y)

    double m = 0.25,  m2 = 0.75;
    double x1 = x+m*dx,  y1 = y+m*dy;
    double x2 = x+m2*dx,  y2 = y+m2*dy;
    double x3 = nx+m*ndx,  y3 = ny+m*ndy;

    double x12 = x+0.5*dx,  y12 = y+0.5*dy;
    double x23 = nx+0.5*ndx,  y23 = ny+0.5*ndy;

    switch ( style )
    {
    case 0:  // as in fxtbook (roundish corners, default)
        tex_line_fl(x1, y1,  x2, y2,  vq);
        tex_line_fl(x2, y2,  x3, y3,  vq);
        break;

    case 1:  // zig-zag (second figure in fxtbook)
        tex_line_fl(x12, y12,  x23, y23,  vq);
        break;

    case 2:  // (roundish corners, only one arrow head)
        tex_line_fl(x1, y1,  x2, y2,  vq);
        tex_line_fl(x2, y2,  x3, y3,  false);
        break;

    default:
        jjassert( 0 );
        break;
//    x = chop0(x);  y = chop0(y);
//    x1 = chop0(x1);  y1 = chop0(y1);
//    nx = chop0(nx);  ny = chop0(ny);
//    x2 = chop0(x2);  y2 = chop0(y2);
//    x3 = chop0(x3);  y3 = chop0(y3);
//
//    double nnx = nx + ndx,  nny = ny + ndy;  // second-next (x, y)
//    double x4 = nx + m2*ndx,  y4 = ny+m2*ndy;
//    nnx = chop0(nnx);  nny = chop0(nny);
//    x4 = chop0(x4);  y4 = chop0(y4);
//    cout << "\\qbezier"
//         << "(" << x1 << "," << y1 << ")"
////         << "(" << x2 << "," << y2 << ")"
//         << "(" << nx << "," << ny << ")"
////         << "(" << x3 << "," << y3 << ")"
//         << "(" << x4 << "," << y4 << ")"
//         << ""
//         << endl;
    }
}
// -------------------------
