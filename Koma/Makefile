# For gcc
CC = g++

#For Optimization
CFLAGS = -O2
#For debugging
#CFLAGS = -g

RM= /bin/rm -f

.cpp.o: 
	$(CC) -c $(CFLAGS) $<

all:	Koma.a HanTag.a Koma HanTag KUTagger

Koma.a:	Koma.o KomaRsc.o core.o hcc98.o ph.o predict.o FST.o KomaAPI.o
	ar -r $@ Koma.o KomaRsc.o core.o hcc98.o ph.o predict.o FST.o KomaAPI.o

HanTag.a:	Tagger.o TaggerRsc.o Taganal.o FST.o HanTagAPI.o
	ar -r $@ Tagger.o TaggerRsc.o Taganal.o FST.o HanTagAPI.o

Koma:	KomaMain.o Koma.a
	$(CC) -o ../bin/$@ KomaMain.o Koma.a -lm

HanTag:	HanTagMain.o HanTag.a Koma.a
	$(CC) -o ../bin/$@ HanTagMain.o HanTag.a Koma.a -lm

KUTagger:	KUTagger.o Koma.a HanTag.a
	$(CC) -o ../bin/$@ KUTagger.o Koma.a HanTag.a -lm

clean:
	rm -f *.o *.a
