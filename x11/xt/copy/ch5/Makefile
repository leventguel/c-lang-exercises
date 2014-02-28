CC = cc 
DEBUG = -O

#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2
# else
CFLAGS = $(DEBUG) 

# If SUN, use this lib
#LIBS =  -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  
#if sgi use
LIBS =  -lXm -lXt -lX11 -lPW

TARGETS= explicit formtest formtest2 layout frame pane mainwindow radiobox rctest scale scroll traverse twoshells

all: $(TARGETS)

explicit: explicit.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

formtest: formtest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
formtest2: formtest2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
layout: layout.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
form3: form3.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

frame: frame.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

pane: pane.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
mainwindow: mainwindow.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
radiobox: radiobox.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
rctest: rctest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

scale: scale.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

traverse: traverse.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
twoshells: twoshells.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
scroll: scroll.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)



clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

