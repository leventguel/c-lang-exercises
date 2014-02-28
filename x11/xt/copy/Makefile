SHELL=/bin/sh

DIRS=lib  ch2 ch3 ch4 ch5 ch6 ch7 ch8 ch9 ch10 ch11 ch12 ch13 ch14 ch15 ch16 ch17

all: 
	for d in ${DIRS}; do \
	cd $$d;  echo `pwd`; make; cd ..; \
	done

clobber:
	for d in ${DIRS}; do \
	cd $$d; echo `pwd`; make clobber; cd ..; \
	done

