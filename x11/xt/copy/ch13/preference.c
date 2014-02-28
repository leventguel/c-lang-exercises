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

/*********************************************************
  * preference.c: Implement a preference dialog to allow
  *               customization of the fractal image.
  *********************************************************/
#include <Xm/Xm.h> 
#include <Xm/Scale.h> 
#include <Xm/ToggleB.h> 
#include <Xm/MessageB.h> 
#include <Xm/RowColumn.h>
#include <math.h> 
#include "fractal.h"

typedef struct  {
  char    *name;
  float    multiplier;
  Widget   w;
  int      value;
} SliderData;

static void OkCallback ( Widget    w,        
                         XtPointer clientData, 
                         XtPointer callData );
static void CancelCallback ( Widget    w,
                             XtPointer clientData, 
                             XtPointer callData );
extern void CreateImage ( ImageData *data );
extern void SetupColorMap ( Widget shell, ImageData *data, Boolean ramp );
void  UpdatePreferences ( ImageData *data );

typedef enum { DEPTH, RANGE, DIST, REAL, IMAG, NCOLORS } PreferenceTypes;

static SliderData sliders [] = {
  { "depth"      },
  { "range"      },
  { "distance"   },
  { "realOrigin" },
  { "imagOrigin" }
};

static Widget         toggle;
static Widget         colorMapToggle;
static Widget         dialog = NULL;
static ColorationType currentColoration;
            
void ShowPreferences ( Widget parent, ImageData *data ) 
{
    Widget rowColumn;
    int    i;

    /*
     * If this is the first time this function has been called
     * create the preference dialog.
     */

    if ( !dialog ) 
    {
        Arg args[1];

       /*
        * Use a message box dialog widget, and remove the symbol
        * and label areas. This dialog is designed to allow the user
        * to apply data or to dismiss the dialog, so XmNautoUnmanage
        * is also set to FALSE.
        */

        XtSetArg ( args[0], XmNautoUnmanage, FALSE );
        dialog = XmCreateMessageDialog ( parent, "preferences",
                                         args, 1 );
        XtUnmanageChild (  XmMessageBoxGetChild ( dialog, 
                                             XmDIALOG_SYMBOL_LABEL ) );
        XtUnmanageChild ( XmMessageBoxGetChild ( dialog,
                                               XmDIALOG_MESSAGE_LABEL ) );

       /* Create the work area */

        rowColumn = 
                  XtVaCreateManagedWidget ( "rowColumn",
                                             xmRowColumnWidgetClass,
                                             dialog,
                                             XmNorientation,XmVERTICAL,
                                             XmNpacking, XmPACK_COLUMN,
                                            XmNnumColumns,  2,
                                            NULL );

      /* Create sliders to control variable values */

       for ( i = 0; i < XtNumber ( sliders ); i++ ) 
       {
           short decimalPoints;
                
           sliders[i].w = XtVaCreateManagedWidget ( sliders[i].name,
                                                    xmScaleWidgetClass,
                                                    rowColumn,
                                                    NULL );
          /*
           * Because the range of each slider can be specified in
           * a resource file, the program must determine the number
           * of decimal points to be used when evaluating a slider 
           * position. Get the value, and convert to a power of ten.
           */

          XtVaGetValues ( sliders[i].w,
                          XmNdecimalPoints, &decimalPoints,
                          NULL );
          sliders[i].multiplier = powf ( 10.0, 
                                         ( double ) decimalPoints );
            
       }

      /* Create toggles to control coloring style */

       toggle = XtCreateManagedWidget ( "colorStyle",
                                        xmToggleButtonWidgetClass,
                                        rowColumn,
                                        NULL, 0 );
       colorMapToggle = 
                    XtCreateManagedWidget ( "colorMap",
                                                 xmToggleButtonWidgetClass,
                                             rowColumn,
                                             NULL, 0 );

      /* 
       * Add callbacks to apply new values and to dismiss the
       * dialog without applying changes.
       */

       XtAddCallback ( dialog, XmNokCallback, 
                       OkCallback, ( XtPointer ) data );
       XtAddCallback ( dialog, XmNcancelCallback, 
                       CancelCallback, ( XtPointer ) data ); 
    }

    /*
     * Post the dialog, first setting all sliders to the
     * current values of the corresponding data.
     */
  
     UpdatePreferences ( data );

    /* 
     * Set the initial value of the coloring toggle
     */
  
     XtVaSetValues ( toggle, XmNvalue,
                     data->coloration == DISTANCE ? TRUE : FALSE, 
                     NULL );
     XtManageChild ( dialog );
}
                                                                                        
void UpdatePreferences ( ImageData *data )
{
    int i;

   /*
    * DonÕt try to update if the dialog doesnÕt exist yet.
    */

    if ( !dialog )
        return;
   /*
    * Multiply each value by the multiplier for each scale to
    * get the correct integer value for each scale.
    */

    sliders[DEPTH].value  = data->depth * sliders[DEPTH].multiplier;
    sliders[REAL].value   = data->origin.real * 
                                          sliders[REAL].multiplier;
    sliders[IMAG].value   = data->origin.imag * 
                                             sliders[IMAG].multiplier;
    sliders[RANGE].value  = data->range * sliders[RANGE].multiplier;
    sliders[DIST].value   = data->maxDistance * 
                                           sliders[DIST].multiplier;
    sliders[NCOLORS].value   = data->ncolors;

   /*
    * Move each scale to the correct position.
    */

    for ( i = 0; i < XtNumber ( sliders ); i++ ) 
       XtVaSetValues ( sliders[i].w, 
                       XmNvalue, sliders[i].value,
                       NULL );

}
                

static void OkCallback ( Widget    w, 
                         XtPointer clientData,
                         XtPointer callData ) 
{
    int i;
    ImageData *data = ( ImageData * ) clientData;

   /*
    * Retrieve the current values from all sliders and
    * store in the ImageData structure.
    */

    for ( i = 0; i < XtNumber ( sliders ); i++ ) 
        XtVaGetValues ( sliders[i].w,
                        XmNvalue, &( sliders[i].value ),
                        NULL );

    data->depth       = sliders[DEPTH].value / 
                                          sliders[DEPTH].multiplier;
    data->origin.real = sliders[REAL].value  /
                                          sliders[REAL].multiplier;
    data->origin.imag = sliders[IMAG].value  /
                                          sliders[IMAG].multiplier;
    data->range       = sliders[RANGE].value / 
                                          sliders[RANGE].multiplier;
    data->maxDistance = sliders[DIST].value /
                                          sliders[DIST].multiplier;
    data->ncolors     =  sliders[NCOLORS].value;
    
   /* 
    * Update the color style according to the toggle setting
    */

    if ( XmToggleButtonGetState ( toggle ) ) 
        data->coloration = DISTANCE;
    else
        data->coloration = ITERATIONS;

    SetupColorMap ( data->canvas, data,
                    XmToggleButtonGetState ( colorMapToggle ) );
   /* 
    * Recompute and redisplay the fractal.
    */

    CreateImage ( data );  
}
                    
static void CancelCallback ( Widget    w,
                             XtPointer clientData,
                             XtPointer callData ) 
{
    /*
     * Just unmanage the dialog without updating any values.
     */

     XtUnmanageChild ( w );
}
        
