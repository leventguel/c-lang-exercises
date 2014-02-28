CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11
.o:.c

all: getpixel coloredit 

getpixel : getpixel.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
coloredit : coloredit.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)


