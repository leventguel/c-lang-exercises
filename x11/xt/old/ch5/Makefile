CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: xbc trackmouse1 trackmouse2  select trackmouse3 xclock stopwatch


trackmouse1: mousetracks.o tracker1.o
	$(CC) $(CFLAGS) -o $@ mousetracks.o tracker1.o  $(LIBS)

trackmouse2 : mousetracks.o tracker2.o
	$(CC) $(CFLAGS) -o $@ mousetracks.o tracker2.o $(LIBS)

trackmouse3 : mousetracks.o tracker3.o
	$(CC) $(CFLAGS) -o $@ mousetracks.o tracker3.o $(LIBS)

select : select.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

xclock : xclock.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

xbc : xbc.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

stopwatch : stopwatch.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)


