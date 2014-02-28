CC = cc
DEBUG = -O
#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2  -I../lib 
# else
CFLAGS = $(DEBUG) 

# If SUN, use this lib
#LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L../lib -lXs -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  
#if sgi use
#LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lPW

LIBS =  -L../lib -lXm -lXt -lX11

TARGETS=customdialog customdialog2 customdialog3 dialogdemo dialogdemo2 filedemo xecute askquestion

all: library $(TARGETS)


library:
	cd ../lib; make

customdialog: customdialog.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
customdialog2: customdialog2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
customdialog3: customdialog3.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
dialogdemo: dialogdemo.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
dialogdemo2: dialogdemo2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
filedemo: filedemo.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
xecute: xecute.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
askquestion: askquestion.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

clean:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

