CC = cc 
XSLIBDIR = ../lib
DEBUG = -g
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: fileview fileview2 fileview3 fileview4

fileview: fileview.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

fileview2: fileview2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

fileview3: fileview3.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

fileview4: fileview4.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

