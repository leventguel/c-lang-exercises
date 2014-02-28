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

/************************************************
  * pushbutton.c: Test the XmPushButton widget.
  *************************************************/
 #include <Xm/Xm.h> 
 #include <Xm/PushB.h>
 #include <stdio.h>

 void buttonCallback ( Widget    w, 
                       XtPointer clientData, 
                       XtPointer callData );

void main ( int argc, char **argv ) 
{
   Widget       shell, button;
   XtAppContext app;       

   /*
    * Initialize Xt
    */

   shell = XtAppInitialize ( &app, "Pushbutton", NULL, 0, 
                             &argc, argv, NULL, NULL, 0 );

  /* 
   * Create the pushbutton widget. 
   */ 

  button =  XtCreateManagedWidget ( "button",
                                     xmPushButtonWidgetClass,
                                     shell, NULL, 0 );
  /*  
   * Add a callback for each supported callback list. 
   */ 

  XtAddCallback ( button, XmNactivateCallback,
                  buttonCallback, NULL);
  XtAddCallback ( button, XmNarmCallback, 
                  buttonCallback, NULL );
  XtAddCallback ( button, XmNdisarmCallback, 
                  buttonCallback, NULL ); 

  XtRealizeWidget ( shell );
  XtAppMainLoop ( app );
}


void buttonCallback ( Widget w, XtPointer clientData, XtPointer callData ) 
{
     XmAnyCallbackStruct *cbs = (XmAnyCallbackStruct *) callData;

     switch(cbs->reason)
     {
       case XmCR_ACTIVATE:
          printf("Button activated\n"); 
          break;
       case XmCR_ARM:
          printf("Button armed\n"); 
          break;
       case XmCR_DISARM:
         printf("Button disarmed\n");
         break;
    } 
}

