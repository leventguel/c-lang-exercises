CC = cc 
DEBUG = -g
CFLAGS = $(DEBUG) -DSYSV -I../../lib -fullwarn

LIBS =  -L../../lib -lXs -lXm -lXt -lX11 -lPW

TARGETS= draw

all: $(TARGETS)

draw: editor.o graphics.o main.o
	$(CC) $(CFLAGS) -o $@  main.o editor.o graphics.o  $(LIBS)



clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

