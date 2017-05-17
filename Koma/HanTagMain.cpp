#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HanTagAPI.h"
#include "nlp.def"

#define ProbEntryFilename "prob.FST"
#define ProbDataFilename "prob.dat"

int ReadMTWrd (FILE* DocFile, char **Wrdp, char *Tag[MaxNumAmb]) 
{
  int i, j, len;
  int NumAmb;

  char Line[BuffSize];
  char Buffer[BuffSize];

  /* 매개변수 초기화 */
  (*Wrdp)=Tag[0]=NULL;

  /* Document File에서 한 단어를 읽는다. */
  /* EOF이면 -1을 반환한다.              */
  if (fgets(Line, BuffSize, DocFile)==NULL) return -1;

  /* 줄이 너무 길면 오류 처리 */
  len=strlen(Line);
  if ((len==BuffSize-1)&&(Line[len-1]!='\n')) {
    fprintf(stderr, "[warning] too long line!\n%s\n", Line);
    fprintf(stderr, "          The remainder will be ignored.\n");
    for (i=len-1; Line[i]!=AmbMark[0]; i--);
    len=i+1;
    while(getc(DocFile)!='\n');
  } /* if */

  /* 마지막의 \n을 잘라낸다. */
  Line[len-1]='\0';

  /* 공백이면 -2를 반환한다. */
  if (Line[0]=='\0') return -2;

  /* 단어를 Wrd에 저장한다. */
  i=j=0;
  while ((Line[i]!=WrdTagMark[0])&&(Line[i]!='\0')) Buffer[j++]=Line[i++];
  Buffer[j]='\0';

  len=strlen(Buffer);
  if (((*Wrdp)=(char*)calloc(len+1, sizeof(char)))==NULL) {
    fprintf(stderr, "[error] cannot allocate memory!!\n   ===> %s\n", Line);
    return -1;
  } /* if */

  strcpy((*Wrdp), Buffer);

  /* Tag가 존재하지 않으면 0을 return */
  if ((Line[i]!=WrdTagMark[0])||((Line[i]==WrdTagMark[0])&&(Line[i+1]=='\0'))) return 0;

  /* 분석을 Tag에 저장한다. */
  for (NumAmb=0; (Line[i]!='\0')&&(NumAmb<MaxNumAmb-1); NumAmb++) {
    i++; j=0;     	/* skip AmbMark[0] or WrdTagMark[0] */
    while ((Line[i]!=AmbMark[0])&&(Line[i]!='\0')) Buffer[j++]=Line[i++];
    Buffer[j]='\0';

    len=strlen(Buffer);
    if ((Tag[NumAmb]=(char *)calloc(len+1, sizeof(char)))==NULL) {
      fprintf(stderr, "[error] cannot allocate memory!!\n   ===> %s\n", Line);
      return -1;
    } /* if */

    strcpy(Tag[NumAmb], Buffer);
  } /* for (NumAmb) */

  if (NumAmb==MaxNumAmb-1) {
    fputs("[warning] too many Ambiguity, the remainder will be ignored!!\n          ==> ", stderr);
    fputs((*Wrdp), stderr);
    fputc('\n', stderr);
  } /* if */

  Tag[NumAmb]=NULL;

  return NumAmb;
} /* ReadMTWrd */

int ReadMTSen (FILE *DocFile, char *Wrd[MaxNumWrd], char *Tag[MaxNumWrd][MaxNumAmb]) 
{
  int NumWrd=0;
  int NumAmb;

  /* 빈칸은 모두 skip한다. */
  do NumAmb=ReadMTWrd(DocFile, &Wrd[0], Tag[0]);
  while ((NumAmb!=-1)&&(NumAmb==-2));

  /* 화일끝에 도달하면 -1을 반환한다.*/
  if (NumAmb==-1) return -1;

  /* 빈칸이나 EOF가 나올때까지 단어를 읽는다. */
  do {
    NumWrd++;
    if (NumWrd==MaxNumWrd-1) {
      fprintf(stderr, "[warning] too many words in a sentence !\n       => %s %s ...\n", Wrd[0], Wrd[1]);
      fprintf(stderr, "          The remainder will be ignored.\n");
      break;
    } /* if */
    NumAmb=ReadMTWrd(DocFile, &Wrd[NumWrd], Tag[NumWrd]);
  } while ((NumAmb!=-1)&&(NumAmb!=-2));

  /* 문장의 끝 표시를 한다. */
  Wrd[NumWrd]=NULL;
  Tag[NumWrd][0]=NULL;

  return NumWrd;
} /* ReadMTSen */

int main(int argc, char *argv[])
{
  char *Wrd[MaxNumWrd]={0,};
  char *Cnd[MaxNumWrd][MaxNumAmb]={{0,},};
  char *Result[MaxNumWrd][MaxNumAmb];
  void *HanTag;
  int i;

  if (LoadHanTagEngine(ProbEntryFilename, ProbDataFilename)==false) {
    fprintf(stderr, "ERROR :: cannot load HanTag engine\n");
    return 1;
  }

  if ((HanTag=CreateHanTag())==NULL) {
    fprintf(stderr, "ERROR :: cannot make HanTag instance\n");
    return 1;
  }

  while (ReadMTSen(stdin, Wrd, Cnd)>0) {
    DoHanTag(HanTag, PATH_BASED_TAGGING, Cnd, Result);
    for (i=0; Result[i][0]; i++) {
      printf("%s%s%s\n", Wrd[i], WrdTagMark, Result[i][0]);
      for (int j=0; Cnd[i][j]; j++) {
        free(Cnd[i][j]);
        Cnd[i][j]=NULL;
      }
      free(Wrd[i]);
    }
    printf("\n");
  }

  FreeHanTag(HanTag);

  EndHanTagEngine();
  return 0;
}
