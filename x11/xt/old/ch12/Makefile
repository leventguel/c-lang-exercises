CC = cc 
XSLIBDIR = ../lib
DEBUG = -g
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11 -lm

.o:.c

all: lib dial sqdial

lib : Dial.o SquareDial.o
	ar ruv ../lib/libXs.a Dial.o SquareDial.o

dial: dial.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

sqdial: sqdial.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

