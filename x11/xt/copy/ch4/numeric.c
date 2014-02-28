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

/*******************************************************************
 * numeric.c: Create an input field that allows only numeric input
 *******************************************************************/
#include <Xm/Xm.h>
#include <Xm/TextF.h>
#include <ctype.h>

/* Callback declarations */

static void TextModifiedCallback ( Widget    w,
                                   XtPointer clientData, 
                                   XtPointer callData );

Widget CreateInputField ( Widget parent )
{
   /* Create a text field widget */

    Widget text = XmCreateTextField ( parent, "input", NULL, 0 );

    XtManageChild ( text );

   /* Add a callback to ensure that all input consists of digits */

    XtAddCallback ( text, XmNmodifyVerifyCallback, 
                    TextModifiedCallback, NULL );

    return ( text );
}

static void TextModifiedCallback ( Widget    w, 
                                   XtPointer clientData, 
                                   XtPointer callData )
{
    XmTextVerifyCallbackStruct *cbs = 
                           ( XmTextVerifyCallbackStruct * ) callData;

   /* 
    * Test all characters of any new input to be sure they are
    * digits only. Set doit to FALSE if any character fails 
    */
  
    if ( cbs->text->ptr )
    {
       char *string = cbs->text->ptr;
       int i;

       for ( i = 0; i < cbs->text->length; i++ )
          if ( !isdigit ( string[i] ) )
              cbs->doit = FALSE;            
    }
}

