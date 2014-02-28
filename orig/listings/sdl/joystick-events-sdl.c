/* Example of simple joystick input with SDL. */

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    SDL_Event event;
    SDL_Joystick *js;
    int num_js, i, quit_flag;

    /* Initialize SDL's joystick and video subsystems. */
    if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
	printf("Error: %s\n", SDL_GetError());
	return 1;
    }

    atexit(SDL_Quit);

    /* Create a 256x256 window so we can collect input events. */
    if (SDL_SetVideoMode(256, 256, 16, 0) == NULL) {
	printf("Error: %s\n", SDL_GetError());
	return 1;
    }

    /* Find out how many joysticks are available. */
    num_js = SDL_NumJoysticks();
    printf("SDL recognizes %i joystick(s) on this system.\n", num_js);
    if (num_js == 0) {
	printf("No joysticks were detected.\n");
	return 1;
    }

    /* Print out information about each joystick. */
    for (i = 0; i < num_js; i++) {

	/* Open the joystick. */
	js = SDL_JoystickOpen(i);

	if (js == NULL) {
	    printf("Unable to open joystick %i.\n", i);
	} else {
	    printf("Joystick %i\n", i);
	    printf("\tName:       %s\n", SDL_JoystickName(i));
	    printf("\tAxes:       %i\n", SDL_JoystickNumAxes(js));
	    printf("\tTrackballs: %i\n", SDL_JoystickNumBalls(js));
	    printf("\tButtons:    %i\n", SDL_JoystickNumButtons(js));

	    /* Close the joystick. */
	    SDL_JoystickClose(js);
	}
    }

    /* We'll use the first joystick for the demonstration. */
    js = SDL_JoystickOpen(0);
    if (js == NULL) {
	printf("Unable to open joystick: %s\n", SDL_GetError());
    }

    /* Loop until the user presses Q. */
    quit_flag = 0;
    while (SDL_WaitEvent(&event) != 0 && quit_flag == 0) {
	switch (event.type) {

	case SDL_KEYDOWN:

	    if (event.key.keysym.sym == SDLK_q) {
		printf("Q pressed. Exiting.\n");
		quit_flag = 1;
	    }

	    break;

	    /* This event is generated when an axis on an open
	       joystick is moved. Most joysticks have two axes,
	       X and Y (which will be reported as axes 0 and 1). */
	case SDL_JOYAXISMOTION:

	    printf("Joystick %i, axis %i movement to %i\n",
		   event.jaxis.which, event.jaxis.axis, event.jaxis.value);

	    break;

	    /* The SDL_JOYBUTTONUP and SDL_JOYBUTTONDOWN events
	       are generated when the state of a joystick button
	       changes. */
	case SDL_JOYBUTTONUP:
	    /* fall through to SDL_JOYBUTTONDOWN */

	case SDL_JOYBUTTONDOWN:

	    printf("Joystick %i button %i: %i\n",
		   event.jbutton.which,
		   event.jbutton.button, event.jbutton.state);

	    break;

	}
    }

    /* Close the joystick. */
    SDL_JoystickClose(js);

    return 0;
}
