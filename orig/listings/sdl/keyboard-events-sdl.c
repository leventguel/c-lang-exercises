/* Example of simple keyboard input with SDL. */

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    SDL_Surface *screen;
    SDL_Event event;

    /* Initialize SDL's video system and check for errors. */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
    }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    /* Attempt to set a 256x256 hicolor (16-bit) video mode. */
    screen = SDL_SetVideoMode(256, 256, 16, 0);
    if (screen == NULL) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
	return 1;
    }

    printf("Press 'Q' to quit.\n");

    /* Start the event loop. Keep reading events until there
       is an error, or the user presses a mouse button. */
    while (SDL_WaitEvent(&event) != 0) {
	SDL_keysym keysym;

	/* SDL_WaitEvent has filled in our event structure
	   with the next event. We check its type field to
	   find out what happened. */
	switch (event.type) {

	case SDL_KEYDOWN:
	    printf("Key pressed. ");
	    keysym = event.key.keysym;
	    printf("SDL keysym is %i. ", keysym.sym);
	    printf("(%s) ", SDL_GetKeyName(keysym.sym));

	    /* Report the left shift modifier. */
	    if (event.key.keysym.mod & KMOD_LSHIFT)
		printf("Left Shift is down.\n");
	    else
		printf("Left Shift is up.\n");

	    /* Did the user press Q? */
	    if (keysym.sym == SDLK_q) {
		printf("'Q' pressed, exiting.\n");
		exit(0);
	    }

	    break;

	case SDL_KEYUP:
	    printf("Key released. ");
	    printf("SDL keysym is %i. ", keysym.sym);
	    printf("(%s) ", SDL_GetKeyName(keysym.sym));

	    if (event.key.keysym.mod & KMOD_LSHIFT)
		printf("Left Shift is down.\n");
	    else
		printf("Left Shift is up.\n");

	    break;

	case SDL_QUIT:
	    printf("Quit event. Bye.\n");
	    exit(0);
	}
    }

    return 0;
}
