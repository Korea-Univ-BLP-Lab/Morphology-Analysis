# For gcc
CC = g++

#For Optimization
CFLAGS = -O2
#For debugging
#CFLAGS = -g

RM= /bin/rm -f

.cpp.o: 
	$(CC) -c $(CFLAGS) $<

all:	MakeDic

MakeDic:	FST.o MakeFSTMain.o MakeDic.o
	$(CC) -o ../bin/$@ FST.o MakeFSTMain.o MakeDic.o -lm

clean:
	rm -f *.o *.a
