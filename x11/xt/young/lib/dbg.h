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

/*********************************************************************
 * dbg.h: Declarations to support a resource to control debug levels
 *******************************************************************/
#ifndef STRINGTODBG_H
#define STRINGTODBG_H
#include <Xm/Xm.h>

/*
 * The type convert function, which must be registered by
 * any program that uses it.
 */

extern Boolean CvtStringToDebugLevel ( Display     *dpy,
				       XrmValue    *args,
				       Cardinal    *nargs,
				       XrmValue    *fromVal,
				       XrmValue    *toVal,
				       XtPointer   *data );

/* Enumerated values used to indicate debugging levels */

typedef enum { LEVEL0, LEVEL1, LEVEL2, LEVEL3, LEVEL4 } DebugLevel;

/* Resource macros defined for convenience */

#define XmNdebugLevel "debugLevel"
#define XmCDebugLevel "DebugLevel"
#define XmRDebugLevel "DebugLevel"
#endif

