#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KomaAPI.h"
#include "HanTagAPI.h"
#include "nlp.def"

#define MainFSTFilename "main.FST"
#define MainDataFilename "main.dat"
#define ConnectionTableFilename "connection.txt"
#define TagFilename "tag.nam"
#define TagOutFilename "tagout.nam"
#define ProbEntryFilename "prob.FST"
#define ProbDataFilename "prob.dat"

void help (void) 
{
    fprintf (stdout, "KUTagger -t : for Path_Based_Tagging,\n");
    fprintf (stdout, "KUTagger -m : for Morphological Analysis,\n");
}

int main(int argc, char *argv[])
{
  char Sentence[10000];
  char *Wrd[MaxNumWrd];
  char *Result[MaxNumWrd][MaxNumAmb];
  void *HanTag;
  int i;
  TaggingMethod m;

  if (LoadKomaEngine(MainFSTFilename, MainDataFilename, ConnectionTableFilename,
                     TagFilename, TagOutFilename)==false) {
    fprintf(stderr, "ERROR :: cannot load KOMA engine\n");
    return 1;
  }

  if (LoadHanTagEngine(ProbEntryFilename, ProbDataFilename)==false) {
    fprintf(stderr, "ERROR :: cannot load HanTag engine\n");
    return 1;
  }

  if ((HanTag=CreateHanTag())==NULL) {
    fprintf(stderr, "ERROR :: cannot make HanTag instance\n");
    return 1;
  }  
  
  if (argc<=1) help ();
  else if (!strcmp ("-t", argv[1]) || !strcmp ("-T", argv[1])) 
  	m = PATH_BASED_TAGGING;
  else if (!strcmp ("-m", argv[1]) || !strcmp ("-M", argv[1])) 
	m = NO_TAGGING;
  else
  {
  	fprintf(stderr,"Invalide option\n");
  	return 1;
  }
  
  //파일을 버퍼로 읽어 들였다면 버퍼의 포인터(*NextToRead)를 넘겨주는 
  //LoadSentenceFromString(&NextToRead, Sentence, MaxSentenceBuffer) 함수를 사용하면 된다.
  
  while (LoadSentenceFromStream(stdin, Sentence, 10000)) {
    DoKomaAndHanTag(HanTag, m, Sentence, Wrd, Result);
    for (i=0; Result[i][0]; i++)
    {
      fprintf(stdout,"%s\t", Wrd[i]);
      for (int j=0; Result[i][j]; j++) {
	if (j) fprintf(stdout, "^");
	fprintf(stdout, "%s", Result[i][j]);
      }
      fprintf(stdout,"\n");            
    }
    fprintf(stdout,"\n");
  }

  FreeHanTag(HanTag);

  EndHanTagEngine();
  EndKomaEngine();
  return 0;
}
