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

/**************************************************
 * xpmlogo.c: Display the X Logo using Xpm format
 **************************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <X11/xpm.h>  /* Non-standard header file */

static char * xlogo16[] = {
"16 16 3 1",
"a c red m black",
". c white m white s background",
"X c blue m black",
"aaaa...........X",
".aaaa..........X",
"..aaaa........X.",
"...aaaa......X..",
"...aaaa.....X...",
"....aaaa...X....",
".....aaaa..X....",
"......aaa.X.....",
"......aa.X......",
"......a.XXX.....",
".....a..XXXX....",
".....a...XXXX...",
"....a....XXXX...",
"...a......XXXX..",
"..a........XXXX.",
".a..........XXXX"};

Widget CreateXlogoButton ( Widget parent );  

void main ( int argc, char **argv )
{
    Widget       shell, button;
    XtAppContext app;
    
    shell = XtAppInitialize ( &app, "XPmlogo", NULL, 0, 
                              &argc, argv, NULL, NULL, 0  );

    button = CreateXlogoButton ( shell );
  
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
                        
Widget CreateXlogoButton ( Widget parent )  
{
    Widget          button;
    Pixmap          pix, mask;
    XpmAttributes   attributes;
    int             status;
    Display         *dpy = XtDisplay ( parent );

   /*
    * Create a button widget
    */

    button = XtCreateManagedWidget ( "button", 
                                     xmPushButtonWidgetClass,
                                     parent, NULL, 0 );
   /*
    * Retrieve the depth and colormap used by this widget
    * and store the results in the corresponding field
    * of an XpmAttributes structure.
    */

    XtVaGetValues ( button,
                    XmNdepth,    &attributes.depth,
                    XmNcolormap, &attributes.colormap,
                    NULL);

   /*
    * Specify the visual to be used and set the XpmAttributes mask.
    */

    attributes.visual = DefaultVisual ( dpy, DefaultScreen ( dpy ) );
    attributes.valuemask = XpmDepth | XpmColormap | XpmVisual;

   /*
    * Create the pixmap
    */

    status = XpmCreatePixmapFromData ( dpy,
                                       DefaultRootWindow ( dpy ), 
                                       xlogo16, &pix, &mask,
                                       &attributes );
    /*
     * The mask isn't used, so free it if one was created.
     */

     if ( mask )
        XFreePixmap( dpy, mask );
    /*
     * Install the pixmap in the button
     */
     
     if ( status == XpmSuccess ) 
         XtVaSetValues ( button, XmNlabelType, XmPIXMAP,
                         XmNlabelPixmap, pix,
                         NULL );
    return ( button );
}
                            
