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

/*******************************************************
 * setupicon2.c: Create a window to display an Xpm
 *               color window manager icon
 *******************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <X11/xpm.h>

void SetupIcon ( Widget shell, char **xpmDesc )
{
    Pixmap          pix;
    XpmAttributes   attributes;
    int             status;
    Display        *dpy = XtDisplay ( shell );
    Widget          icon_shell, label;

   /*
    * Create a shell widget, and set mappedWhenManaged to FALSE.
    * The windowe manager controls when this window is mapped.
    */

    icon_shell = XtVaAppCreateShell ( "icon_shell", "Icon_shell", 
                                      topLevelShellWidgetClass, dpy, 
	                                      XmNmappedWhenManaged, FALSE,
	                                      NULL );

   /*
    * Create a label to display the pixmap
    */

    label = XtCreateManagedWidget ( "button", 
                                     xmLabelWidgetClass,
                                     icon_shell, NULL, 0 );
   /*
    * Retrieve the depth and colormap used by this widget
    * and store the results in the corresponding field
    * of an XpmAttributes structure.
    */

    XtVaGetValues ( label,
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
                                        xpmDesc, &pix, NULL,
                                        &attributes );
   /*
    * Install the pixmap in the label
    */
    
    if ( status == XpmSuccess ) 
       XtVaSetValues ( label, 
                       XmNlabelType,   XmPIXMAP,
                       XmNlabelPixmap, pix,
                       NULL );
   /*
    * Realize the icon shell to force the shell’s window to exist
    */

    XtRealizeWidget ( icon_shell );

   /*
    * Install the icon_shell's window as the icon window.
    */

    XtVaSetValues ( shell, XmNiconWindow, 
                    XtWindow ( icon_shell ), NULL );
}

#include <Xm/Label.h>       /* Required by XmLabel widget */

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


void main ( int argc, char **argv )
{
    Widget       shell, msg; /* Widgets created by this application */
    XtAppContext app;        /* An application context, needed by Xt */
    XmString     xmstr;      /* Compound string used by Motif */

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Hello", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    xmstr = XmStringCreateLtoR ( "Hello", XmFONTLIST_DEFAULT_TAG );

   /*
    * Create a Motif XmLabel widget to display the string
    */

    msg = XtVaCreateManagedWidget ( "hello", 
                                    xmLabelWidgetClass, shell, 
                                    XmNlabelString,     xmstr,
                                    NULL );

    XmStringFree ( xmstr );  /* Free the compound string */

   /*
    * Realize the shell and enter an event loop.
    */


    SetupIcon(shell, xlogo16);
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

                                                        
