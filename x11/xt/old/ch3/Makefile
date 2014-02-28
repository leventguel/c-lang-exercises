CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: rmtest rmtest2 rmtest3  draw

rmtest : rmtest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

draw : draw.o
	$(CC) $(CFLAGS) -o $@ $@.o -lXm -lXt -lX11

rmtest2 : rmtest2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

rmtest3 : rmtest3.o 
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

