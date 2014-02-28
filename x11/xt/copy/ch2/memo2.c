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

/*************************************************
 * memo2.c: Display a string on the screen
 *          Allow users to exit by typing a "Q"
 *************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <stdio.h>
#include <stdlib.h>

/* Dclaration of Action function */

static void QuitAction ( Widget    w, 
                         XEvent   *ev,
                         String   *params, 
                         Cardinal *numParams );

/* Register the function quitAction under the symbolic name "bye" */

 static XtActionsRec actionsTable [] = {
   { "bye",   QuitAction },
};

/* Bind the action "bye()" to typing the key "Q" */

static char defaultTranslations[] =  "<Key>Q:  bye()";
 
void main ( int argc, char **argv )
{
    Widget         shell, msg;
    XtAppContext   app;
    XmString       xmstr;
    XtTranslations transTable; /* Compiled translations */

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Memo",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    if ( argc != 2 ) /* Make sure there is exactly one argument */
    {
        fprintf (stderr, "Usage:  memo message-string\n" );
        exit ( 1 );
    }

   /* Register the action functions */

    XtAppAddActions ( app, actionsTable, XtNumber ( actionsTable ) );

   /* Compile the translation table */

    transTable =  XtParseTranslationTable ( defaultTranslations );

   /* Convert the first argument to the form expected by Motif */

    xmstr = XmStringCreate ( argv[1], XmFONTLIST_DEFAULT_TAG );

   /*
    * Create the XmLabel widget
    */

    msg = XtVaCreateManagedWidget ( "message", 
                                    xmLabelWidgetClass, shell, 
                                    XmNlabelString,     xmstr,
                                    NULL );

    XmStringFree ( xmstr );  /* Free the compound string */

   /*
    * Merge the new translations with any existing
    * translations for the label widget.
    */

    XtAugmentTranslations ( msg, transTable );

   /*
    * Realize the shell and enter the event loop.
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

static void QuitAction ( Widget    w, 
                         XEvent   *ev, 
                         String   *params, 
                         Cardinal *numParams )
{
    exit ( 0 );
}

