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


/**********************************************************
 * pipe.c: connect input and out of two programs
 ************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void SetUpTwoWayPipe ( const char *cmd ) 
{
    int to_child[2]; /* pipe descriptors from parent->child */
    int to_parent[2];/* pipe descriptors from child->parent */
    int   pid;
    
    pipe ( to_child );
    pipe ( to_parent );
    
    if  ( pid = fork () , pid == 0 )   /* in the child   */
    { 
        close ( 0 );                    /* redirect stdin */
        dup ( to_child[0] );
        close ( 1 );                    /* redirect stdout*/
        dup ( to_parent[1] );
        close ( to_child[0] );          /* close pipes    */
        close ( to_child[1] );
        close ( to_parent[0] );
        close ( to_parent[1] );
        execlp ( cmd, cmd, NULL );      /* exec the new cmd */
    }
    else if  ( pid > 0 )                 /* in the parent  */
    {           
        close ( 0 );                   /* redirect stdin */
        dup ( to_parent[0] );
        close ( 1 );                   /* redirect stdout  */
        dup ( to_child[1] );
        setbuf ( stdout, NULL );       /* no buffered output */
        close ( to_child[0] );         /* close pipes */
        close ( to_child[1] );
        close ( to_parent[0] );
        close ( to_parent[1] );
    }
    else                        /* error!       */
    {
        fprintf ( stderr,"Couldn't fork process %s\n", cmd );
        exit ( 1 );
    }
}

