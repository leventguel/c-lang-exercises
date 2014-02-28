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
 * calc.c: The CreateCalculator() function and 
 *         other supporting functions.
 ************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/PanedW.h>
#include <Xm/RowColumn.h>
#include <Xm/TextF.h>

/* Declarations of private functions */

static Widget CreateButton ( char *name, Widget parent );
static void QuitCallback ( Widget    w,
                           XtPointer clientData, 
                           XtPointer callData );
static void SendToBc ( Widget     w,
                        XtPointer clientData, 
                        XtPointer callData );
static void  GetFromBc ( XtPointer  clientData, 
                         int       *fid, 
                         XtInputId *id );

/* Calculator output display and related function */

static Widget  displayWidget;
static void    AppendToDisplay ( char *buf );
static void    ClearDisplay ( void );
static char   *DisplayedString ( void );

/* Declare the function used to setup communication with bc */

extern void SetUpTwoWayPipe ( char *cmd );
                                
Widget CreateCalculator ( Widget parent ) 
{
    Widget panel, keyboard, qbutton;

   /*
    * Create a vertical paned widget as a base for the 
    * rest of the calculator.
    */
    
    panel = XtCreateManagedWidget ( "panel", xmPanedWindowWidgetClass,
                                    parent, NULL, 0 );
   /*
    * Create the calculator display widget.
    */
    
    displayWidget = 
            XtVaCreateManagedWidget ( "display",
                                      xmTextFieldWidgetClass,
                                      panel, 
                                      XmNeditable, FALSE,
                                      XmNcursorPositionVisible, FALSE,
                                      NULL );
   /*
    * Make the keyboard, which manages 5 rows of buttons
    */
    
    keyboard = XtVaCreateManagedWidget ( "keyboard", 
                                         xmRowColumnWidgetClass,
                                         panel, 
                                         XmNorientation, XmHORIZONTAL,
                                         XmNnumColumns,  5,
                                         XmNadjustLast,  False,
                                         XmNpacking,    XmPACK_COLUMN,
                                         NULL );
   /* 
    * Create the keyboard buttons. This order makes it 
    * look like a typical desktop calculator.
    */
    CreateButton ( "1", keyboard );
    CreateButton ( "2", keyboard );
    CreateButton ( "3", keyboard );
    CreateButton ( "+", keyboard );
    CreateButton ( "4", keyboard );
    CreateButton ( "5", keyboard );
    CreateButton ( "6", keyboard );
    CreateButton ( "-", keyboard );
    CreateButton ( "7", keyboard );
    CreateButton ( "8", keyboard );
    CreateButton ( "9", keyboard );
    CreateButton ( "*", keyboard );
    CreateButton ( "0", keyboard );
    CreateButton ( ".", keyboard );
    CreateButton ( "=", keyboard );
    CreateButton ( "/", keyboard );
    
   /*
    *  Create a quit button and add a callback to
    *  handle exiting bc.
    */

   qbutton = XtCreateManagedWidget ( "quit",
                                     xmPushButtonWidgetClass,
                                    keyboard, NULL, 0 );    
   XtAddCallback ( qbutton, XmNactivateCallback, QuitCallback, NULL );
    
  /* 
   * Add callback GetFromBc () --  invoked when input 
   * is available from stdin.
   */
    
   XtAppAddInput ( XtWidgetToApplicationContext ( parent ),
                   fileno ( stdin ), ( XtPointer ) XtInputReadMask,
                   GetFromBc, NULL );
    
  /* 
   * Exec the program "bc" and set up pipes 
   * between it and and the calculator process.
   */
    
   SetUpTwoWayPipe ( "bc" );  
   return ( panel );
}
                                                    
static Widget CreateButton ( char *name, Widget parent ) 
{
    Widget      button;  

   /*
    * Create a single button and attach an activate callback.
    */
    
    button = XtCreateManagedWidget ( name, xmPushButtonWidgetClass,
                                     parent, NULL, 0 );
    XtAddCallback ( button, XmNactivateCallback, SendToBc, name );
    
    return ( button );
}
        
static void QuitCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData ) 
{
   /*
    * Tell bc to quit, then exit.
    */

    fprintf ( stdout, "quit\n" );
    exit ( 0 );
}
        
static void SendToBc ( Widget    w, 
                       XtPointer clientData, 
                       XtPointer callData ) 
{
    char     *buffer = ( char * ) clientData;
    XmAnyCallbackStruct *cb;

    static int  startNewEntry = TRUE;

   /*
    * If this is the beginning of a new operand, 
    * clear the display.
    */

    if ( startNewEntry ) 
    {
        ClearDisplay ();
        startNewEntry = FALSE;
    }

    switch ( buffer[0] ) 
    {

     /*
      * If the user entered and '=', send bc a newline, clear
      * the display, and get ready for a new operand.
      */

      case '=':

        fprintf ( stdout, "%s", DisplayedString () );       
        fprintf ( stdout, "\n" );
        ClearDisplay ();
        startNewEntry = TRUE;
        break;

     /*
      * If this is an operator, get the previous operand
      * from the display buffer, and send it to bc before 
      * sending the operand.
      */

      case '-':
      case '+':
      case '/':
      case '*':
      case '^':
      
        fprintf ( stdout, "%s", DisplayedString () );  
        fprintf ( stdout, "%s", buffer );
        ClearDisplay ();
        break;

     /*
      * Anything else must be a digit, so append it to the
      * display buffer.
      */

      default:

        AppendToDisplay ( buffer );
   }

   fflush ( stdout );
}
                                        
static void AppendToDisplay ( char *buf ) 
{
    XmTextFieldInsert ( displayWidget, 
                        XmTextFieldGetLastPosition ( displayWidget ),
                        buf );
}
    
static char *DisplayedString () 
{
    return ( XmTextFieldGetString ( displayWidget ) );
}
    
static void ClearDisplay () 
{

   /*
    * Clear the text buffer and go to position 1.
    */
    
    XmTextFieldSetString ( displayWidget, "" );
    XmTextFieldSetInsertionPosition ( displayWidget, 0 );
}
        
static void GetFromBc ( XtPointer clientData, int *fid, XtInputId *id ) 
{
    char       buf[BUFSIZ];
    int        nbytes, i;
    
   /* 
    * Get all pending input and append it to the display 
    * widget. Discard lines that begin with a newline.
    */
    
    nbytes = read ( *fid, buf, BUFSIZ );
    
    if ( nbytes && buf[0] != '\n' ) 
    {

       /*
        * Null terminate the string at the first newline,
        * or at the end of the bytes read.
        */
        
        for ( i=0;i<nbytes;i++ ) 
            if ( buf[i] == '\n' ) 
                buf[i] = '\0';
        
        buf[nbytes] = '\0'; 

        AppendToDisplay ( buf );
    }
}
                    
