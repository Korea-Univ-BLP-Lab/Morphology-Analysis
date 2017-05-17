#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nlp.def"
#include "KomaAPI.h"

#define MainFSTFilename "main.FST"
#define MainDataFilename "main.dat"
#define ConnectionTableFilename "connection.txt"
#define TagFilename "tag.nam"
#define TagOutFilename "tagout.nam"

int main(int argc, char *argv[])
{
  char s[BuffSize], Result[MaxNumWrd][BuffSize];
  void *Koma;
  int i;

  if (LoadKomaEngine(MainFSTFilename, MainDataFilename, ConnectionTableFilename,
                     TagFilename, TagOutFilename)==false) {
    fprintf(stderr, "ERROR :: cannot load KOMA engine\n");
    return 1;
  }

  if ((Koma=CreateKoma(1/*¿Ï¼ºÇü*/))==NULL) {
    fprintf(stderr, "ERROR :: cannot make KOMA instance\n");
    return 1;
  }
  while (scanf("%s", s)!=EOF) {
    DoKomaOneWord(Koma, s, Result);
    printf("%s%s", s, WrdTagMark);
    for (i=0; Result[i][0]; i++)
      if (i==0)
        printf("%s", Result[i]);
      else printf("%s%s", AmbMark, Result[i]);
    printf("\n");
    if (s[strlen(s)-1]=='.') printf("\n");
  }
  FreeKoma(Koma);

  EndKomaEngine();
  return 0;
}
