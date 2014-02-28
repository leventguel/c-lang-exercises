# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O2

SDL_LIB=`sdl-config --libs`
SDL_IMAGE_LIB=-lSDL_image
OPENGL_LIB=-L/usr/X11R6/include -lGL

SDL_TARGETS=audio-sdl blitting-surfaces-sdl colorkeys-sdl direct-pixel-drawing-sdl initializing-sdl joystick-events-sdl keyboard-events-sdl mouse-events-sdl sdl-anim1 sdl-anim2 sdl-threading
IMAGE_TARGETS=alpha-sdl
OPENGL_TARGETS=opengl-sdl

CC=gcc

.PHONY: default clean all-examples sdl-examples image-examples opengl-example


default:
	@echo 'Valid targets are:'
	@echo '  clean           - Removes all executables.'
	@echo '  all-examples    - Builds all examples in this directory.'
	@echo '  sdl-examples    - Builds only basic SDL examples.'
	@echo '  image-example s - Builds examples that require SDL_image.'
	@echo '  opengl-examples - Builds examples that require OpenGL.'
	@echo
	@echo 'First, however, please configure the variables in the Makefile.'


clean:
	rm -f $(SDL_TARGETS) $(IMAGE_TARGETS) $(OPENGL_TARGETS)
	rm -f *~

all-examples: sdl-examples image-examples opengl-examples

sdl-examples: $(SDL_TARGETS)

image-examples: $(IMAGE_TARGETS)

opengl-examples: $(OPENGL_TARGETS)


alpha-sdl: alpha-sdl.c
	$(CC) $(CFLAGS) alpha-sdl.c -o alpha-sdl $(SDL_IMAGE_LIB) $(SDL_LIB)

audio-sdl: audio-sdl.c
	$(CC) $(CFLAGS) audio-sdl.c -o audio-sdl $(SDL_LIB)

blitting-surfaces-sdl: blitting-surfaces-sdl.c
	$(CC) $(CFLAGS) blitting-surfaces-sdl.c -o blitting-surfaces-sdl $(SDL_LIB)

colorkeys-sdl: colorkeys-sdl.c
	$(CC) $(CFLAGS) colorkeys-sdl.c -o colorkeys-sdl $(SDL_LIB)

direct-pixel-drawing-sdl: direct-pixel-drawing-sdl.c
	$(CC) $(CFLAGS) direct-pixel-drawing-sdl.c -o direct-pixel-drawing-sdl $(SDL_LIB)

initializing-sdl: initializing-sdl.c
	$(CC) $(CFLAGS) initializing-sdl.c -o initializing-sdl $(SDL_LIB)

joystick-events-sdl: joystick-events-sdl.c
	$(CC) $(CFLAGS) joystick-events-sdl.c -o joystick-events-sdl $(SDL_LIB)

keyboard-events-sdl: keyboard-events-sdl.c
	$(CC) $(CFLAGS) keyboard-events-sdl.c -o keyboard-events-sdl $(SDL_LIB)
 
mouse-events-sdl: mouse-events-sdl.c
	$(CC) $(CFLAGS) mouse-events-sdl.c -o mouse-events-sdl $(SDL_LIB)

opengl-sdl: opengl-sdl.c
	$(CC) $(CFLAGS) opengl-sdl.c -o opengl-sdl $(SDL_LIB) $(OPENGL_LIB)

sdl-anim1: sdl-anim1.c
	$(CC) $(CFLAGS) sdl-anim1.c -o sdl-anim1 $(SDL_LIB)

sdl-anim2: sdl-anim2.c
	$(CC) $(CFLAGS) sdl-anim2.c -o sdl-anim2 $(SDL_LIB)

sdl-threading: sdl-threading.c
	$(CC) $(CFLAGS) sdl-threading.c -o sdl-threading $(SDL_LIB)
