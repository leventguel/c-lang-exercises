CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: xlogo xlogo2 raster

xlogo : xlogo.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

xlogo2 : xlogo2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

raster : raster.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)



