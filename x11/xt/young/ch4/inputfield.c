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
 * inputfield.c: Create and return a simple text input area
 ************************************************************/
#include <Xm/Xm.h>
#include <Xm/TextF.h>

Widget CreateInputField ( Widget parent )
{
     Widget text = XmCreateTextField ( parent, "input", NULL, 0 );

    XtManageChild ( text );

    return ( text );
}

