/********************************************************************
 *         This example code is from the book:
 *
 *           The X Window System: Programming and Applications with Xt
 *           Second OSF/Motif Edition
 *         by
 *           Douglas Young
 *           Prentice Hall, 1994
 *
 *         Copyright 1994 by Prentice Hall
 *         All Rights Reserved
 *
 *  Permission to use, copy, modify, and distribute this software for 
 *  any purpose except publication and without fee is hereby granted, provided 
 *  that the above copyright notice appear in all copies of the software.
 * *****************************************************************************/

/************************************************************
 * fractal.h: type declarations used in the fractal program
 ************************************************************/
#include <Xm/Xm.h>

typedef struct {
    double  real, imag;
} ComplexNumber;

typedef enum { DISTANCE, ITERATIONS } ColorationType;

/*
 * Assorted information needed to generate and draw the image.
 */

typedef struct {
    Widget         canvas;
    Pixmap         pixmap;
    GC             gc;
    GC             xorGC;   /* used for second version only */
    Dimension      width, height;
    int            depth, ncolors;
    double         range, maxDistance;
    ComplexNumber  origin;
    ColorationType coloration;
} ImageData;

