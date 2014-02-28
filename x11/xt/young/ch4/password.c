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

/****************************************************************
 * password.c: An input field suitable for obtaining a password
 ****************************************************************/
#include <Xm/Xm.h>
#include <Xm/TextF.h>

static char *password = NULL; /* Buffer for storing password */
static int   index = 0;     /* Position of next character in buffer */

/* Function declarations */

static void MotionCallback ( Widget    w, 
                             XtPointer clientData, 
                             XtPointer callData );

static void TextModifiedCallback ( Widget    w,
                                   XtPointer clientData, 
                                   XtPointer callData );

Widget CreateInputField ( Widget parent )
{
   /* Create a text field widget */

    Widget text = XmCreateTextField ( parent, "input", NULL, 0 );

    XtManageChild ( text );

   /* Add callbacks that handle hiding the true input */

    XtAddCallback ( text, XmNmodifyVerifyCallback,
                     TextModifiedCallback, NULL );
    XtAddCallback ( text, XmNmotionVerifyCallback, 
                    MotionCallback, NULL );

    return ( text );
}

char *GetPassword()
{
   return ( password );
}

static void MotionCallback ( Widget     w, 
                             XtPointer clientData, 
                             XtPointer callData )
{
    XmTextVerifyCallbackStruct *cbs =
                           ( XmTextVerifyCallbackStruct * ) callData;

   /* 
    * By disallowing all backward motion, this function disallows
    * backspaces and also simplifies the password maintenance by 
    * disallowing all editing 
    */

    if ( cbs->newInsert < cbs->currInsert ) 
        cbs->doit = FALSE;
}

static void TextModifiedCallback ( Widget    w,
                                   XtPointer clientData, 
                                   XtPointer callData )
{
    XmTextVerifyCallbackStruct *cbs = 
                            ( XmTextVerifyCallbackStruct * ) callData;

   /*
    * Check for invalid operations 
    */

    if  ( cbs->text->ptr == NULL ||       /* Check for NULL text */
          cbs->text->length > 1 )         /* Don't allow paste   */
    {
        cbs->doit = FALSE;
    }
    else /* A new valid character has been entered */
    {
       /* Store the entered text in a buffer */

        password = XtRealloc ( password, sizeof ( char ) * index + 2);
        password [ index++ ] = cbs->text->ptr [ 0 ];
        password [ index ] = '\0';
    
       /* Replace the typed character with an Õ*Õ character */

        cbs->text->ptr [ 0 ] = '*';
    }
}

