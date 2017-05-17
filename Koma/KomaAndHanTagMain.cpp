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

int main(int argc, char *argv[])
{
  char Sentence[10000];
  char *Wrd[MaxNumWrd];
  char *Result[MaxNumWrd][MaxNumAmb];
  void *HanTag;
  int i;

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

  while (LoadSentenceFromStream(stdin, Sentence, 10000)) {
    DoKomaAndHanTag(HanTag, PATH_BASED_TAGGING, Sentence, Wrd, Result);
    for (i=0; Result[i][0]; i++)
      printf("%s%s%s\n", Wrd[i], WrdTagMark, Result[i][0]);
    printf("\n");
  }

  FreeHanTag(HanTag);

  EndHanTagEngine();
  EndKomaEngine();
  return 0;
}
