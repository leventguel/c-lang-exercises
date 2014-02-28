/* Example of OpenGL rendering through SDL. */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* Initialize SDL as usual. */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	printf("Error: %s\n", SDL_GetError());
	return 1;
    }

    atexit(SDL_Quit);

    /* Enable OpenGL double buffering. */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* Set the color depth (16-bit 565). */
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    /* Create a 640x480, 16 bit window with support for
       OpenGL rendering. Unfortunately we won't know
       whether this is hardware accelerated. */
    if (SDL_SetVideoMode(640, 480, 16, SDL_OPENGL) == NULL) {
	printf("Error: %s\n", SDL_GetError());
	return 1;
    }

    /* Set a window title. */
    SDL_WM_SetCaption("OpenGL with SDL!", "OpenGL");

    /* We can now use any OpenGL rendering commands. */
    glViewport(80, 0, 480, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0, 0);
    glVertex3f(0.0, 1.0, -2.0);
    glColor3f(0, 1.0, 0);
    glVertex3f(1.0, -1.0, -2.0);
    glColor3f(0, 0, 1.0);
    glVertex3f(-1.0, -1.0, -2.0);
    glEnd();
    glFlush();

    /* Display the back buffer to the screen. */
    SDL_GL_SwapBuffers();

    /* Wait a few seconds. */
    SDL_Delay(5000);

    return 0;
}
