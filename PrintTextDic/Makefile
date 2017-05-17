# For gcc
CC = g++

#For Optimization
CFLAGS = -O2
#For debugging
#CFLAGS = -g

RM= /bin/rm -f

.cpp.o: 
	$(CC) -c $(CFLAGS) $<

all:	PrintTextDic

PrintTextDic:	FST.o PrintTextDic.o
	$(CC) -o ../bin/$@ FST.o PrintTextDic.o -lm

clean:
	rm -f *.o *.a
