#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FST.h"

#define MaxPOS 96

void PrintUsage(char *Program)
{

  fprintf(stderr, "Dictionary Information Viewer\n");
  fprintf(stderr, " USAGE : %s <FST Filename> <DATA Filename>\n", Program);
  fprintf(stderr, "   ex) %s sait.FST sait.dat > sait.txt\n\n", Program);
}

int main(int argc, char *argv[])
{
  FST *Entry;
  FILE *f;
  int i, n;
  char Line[256];
  char Lex[100];
  unsigned long Info[3];
  char POSTable[MaxPOS][32];

  if ((f=fopen("pos.nam", "rb"))==NULL) {
    fprintf(stderr, "ERROR :: cannot open pos.nam\n");
    return 1;
  }
  for (i=0; i<MaxPOS; i++) {
    fgets(Line, 256, f);
    sscanf(Line, "%s", POSTable[i]);
  }
  fclose(f);

  if (argc!=3) {
    PrintUsage(argv[0]);
    return 1;
  }

  if ((Entry=LoadFST(argv[1]))==NULL) {
    fprintf(stderr, "ERROR :: cannot load FST\n");
    return 1;
  }

  if ((f=fopen(argv[2], "rb"))==NULL) {
    fprintf(stderr, "ERROR :: cannot open data file\n");
    return 1;
  }

  for (i=0; fscanf(f, "%x%x%x", Info, Info+1, Info+2)!=EOF; i++) {
    if (Hash2String(Entry, i, Lex)==NULL) {
      fprintf(stderr, "ERROR :: invalid hash number\n");
      FreeFST(Entry);
      fclose(f);
      return 1;
    }
    printf("%s { ", Lex);
    for (n=0; n<MaxPOS; n++)
      if (Info[n/32]&(1u<<(n%32)))
        printf("%s ", POSTable[n]);
    printf("}\n");
  }

  FreeFST(Entry);
  fclose(f);
  return 0;
}
