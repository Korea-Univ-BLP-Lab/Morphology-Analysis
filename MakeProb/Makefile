# For gcc
CC = g++

#For Optimization
CFLAGS = -O2
#For debugging
#CFLAGS = -g

RM= /bin/rm -f

.cpp.o: 
	$(CC) -c $(CFLAGS) $<

all:	MakeProb

MakeProb:	FST.o MakeFSTMain.o MakeProb.o
	$(CC) -o ../bin/$@ FST.o MakeFSTMain.o MakeProb.o -lm

clean:
	rm -f *.o *.a
