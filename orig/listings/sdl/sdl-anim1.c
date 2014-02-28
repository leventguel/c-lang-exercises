/* Animation with SDL -- first attempt. */

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_PENGUINS	100
#define MAX_SPEED	6

/* This structure stores the information for one
   on-screen penguin. */
typedef struct penguin_s {
    int x, y;			/* position on the screen */
    int dx, dy;			/* movement vector */
} penguin_t, *penguin_p;

/* Array of penguins. */
static penguin_t penguins[NUM_PENGUINS];

/* These are now global variables, for convenience. */
static SDL_Surface *screen;
static SDL_Surface *penguin;

/* This routine loops through the array of penguins and
   sets each to a random starting position and direction. */
static void init_penguins()
{
    int i;

    for (i = 0; i < NUM_PENGUINS; i++) {
	penguins[i].x = rand() % screen->w;
	penguins[i].y = rand() % screen->h;
	penguins[i].dx = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
	penguins[i].dy = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
    }
}

/* This routine moves each penguin by its motion vector. */
static void move_penguins()
{
    int i;

    for (i = 0; i < NUM_PENGUINS; i++) {
	/* Move the penguin by its motion vector. */
	penguins[i].x += penguins[i].dx;
	penguins[i].y += penguins[i].dy;

	/* Turn the penguin around if it hits the edge
	   of the screen. */
	if (penguins[i].x < 0 || penguins[i].x > screen->w - 1)
	    penguins[i].dx = -penguins[i].dx;
	if (penguins[i].y < 0 || penguins[i].y > screen->h - 1)
	    penguins[i].dy = -penguins[i].dy;
    }
}

/* This routine draws each penguin to the screen surface. */
static void draw_penguins()
{
    int i;
    SDL_Rect src, dest;

    for (i = 0; i < NUM_PENGUINS; i++) {

	src.x = 0;
	src.y = 0;
	src.w = penguin->w;
	src.h = penguin->h;

	/* The penguin's position specifies its
	   center. We subtract half of its width
	   and height to get its upper left corner. */
	dest.x = penguins[i].x - penguin->w / 2;
	dest.y = penguins[i].y - penguin->h / 2;
	dest.w = penguin->w;
	dest.h = penguin->h;

	SDL_BlitSurface(penguin, &src, screen, &dest);
    }
}

int main()
{
    SDL_Surface *background;
    SDL_Rect src, dest;
    int frames;

    /* Initialize SDL's video system and check for errors. */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
    }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    /* Attempt to set a 640x480 hicolor (16-bit) video mode. */
    screen = SDL_SetVideoMode(640, 480, 16, 0);
    if (screen == NULL) {
	printf("Unable to set video mode: %s\n", SDL_GetError());
	return 1;
    }

    /* Load the bitmap files. */
    background = SDL_LoadBMP("background.bmp");
    if (background == NULL) {
	printf("Unable to load bitmap.\n");
	return 1;
    }

    penguin = SDL_LoadBMP("smallpenguin.bmp");
    if (penguin == NULL) {
	printf("Unable to load bitmap.\n");
	return 1;
    }

    /* Set the penguin's colorkey. */
    SDL_SetColorKey(penguin,
		    SDL_SRCCOLORKEY,
		    (Uint16) SDL_MapRGB(penguin->format, 0, 0, 255));

    /* Initialize the penguin position data. */
    init_penguins();

    /* Animate 300 frames (approximately 10 seconds). */
    for (frames = 0; frames < 300; frames++) {

	/* Draw the background image. */
	src.x = 0;
	src.y = 0;
	src.w = background->w;
	src.h = background->h;
	dest = src;

	SDL_BlitSurface(background, &src, screen, &dest);

	/* Put the penguins on the screen. */
	draw_penguins();

	/* Ask SDL to update the entire screen. */
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	/* Move the penguins for the next frame. */
	move_penguins();
    }

    /* Free the memory that was allocated to the bitmap. */
    SDL_FreeSurface(background);
    SDL_FreeSurface(penguin);

    return 0;
}
