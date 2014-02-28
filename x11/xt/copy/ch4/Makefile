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

TARGETS= chooseone label pushbutton input  numeric password toggle

all: $(TARGETS)

chooseone: chooseone.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

label: label.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

pushbutton: pushbutton.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

input: driver.o inputfield.o
	$(CC) $(CFLAGS) -o $@ driver.o inputfield.o $(LIBS)

numeric: driver.o numeric.o
	$(CC) $(CFLAGS) -o $@ driver.o numeric.o $(LIBS)

password: driver2.o password.o
	$(CC) $(CFLAGS) -o $@ driver2.o password.o $(LIBS)

toggle: toggle.o
	$(CC) $(CFLAGS) -o $@ toggle.o $(LIBS)


clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

