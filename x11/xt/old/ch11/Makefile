CC = cc 
XSLIBDIR = ../lib
DEBUG = -g
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: controldata monitordata xtalk memo clipboard notepad

controldata : controldata.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

monitordata : monitordata.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

xtalk : xtalk.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

memo : memo.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

clipboard : clipboard.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

notepad : notepad.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)



