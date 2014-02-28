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

/*********************************************
 * xlogo.c: Display a pixmap on the screen
 *********************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>

void main ( int argc, char **argv  )
{
    Widget       shell, label;
    XtAppContext app;
    Pixel        fg, bg;
    Pixmap       pix;

    shell = XtAppInitialize ( &app, "Xlogo", NULL, 0, 
                              &argc, argv, NULL, NULL, 0  );
    
   /*
    * Create an XmLabel widget
    */
    
    label = XtCreateManagedWidget ( "label", xmLabelWidgetClass,
                                    shell, NULL, 0 );

   /* Get the label’s foreground and background colors */

    XtVaGetValues ( label, 
                    XmNforeground, &fg, 
                    XmNbackground, &bg, 
                    NULL );
                
   /*
    * Create a pixmap, using the bitmap file 
    * found in /usr/include/X11/bitmaps
    */

    pix =  XmGetPixmap ( XtScreen ( shell ), "xlogo64", fg, bg );

   /* Display the pixmap in the label */

    XtVaSetValues ( label, XmNlabelType, XmPIXMAP, 
                           XmNlabelPixmap, pix, 
                           NULL );
   /*
    * Realize the shell and enter the event loop.
    */
    
    XtRealizeWidget ( shell  );
    XtAppMainLoop ( app  );
}
                                    
