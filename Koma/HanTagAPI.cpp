#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tagger.h"

int GetCharFromStream(FILE *f, char *c)
{
  if ((c[0]=fgetc(f))==EOF) {
    c[0]=0;
    return false;
  }
  if ((c[0]<0)&&((c[1]=fgetc(f))!=EOF)) 
    c[2]=0;
  else c[1]=0;
  return true;
}

int GetCharFromString(char **s, char *c)
{
  
  if ((s==NULL)||(*s==NULL)||((*s)[0]==0)) return false;
  if (((*s)[0]>0)||((*s)[1]==0)) {
    c[0]=(*s)[0];
    c[1]=0;
    (*s)++;
  }
  else {
    c[0]=(*s)[0];
    c[1]=(*s)[1];
    c[2]=0;
    (*s)+=2;
  }
  return true;
}

#define SpaceChar " \t\r\n"
#define EOSChar ". ? ! 。 ！ ？ ．"
#define QuoteChar "\" ` ' ＇ ＂ ｀ ’ ” ‘ ’ “ ”"
#define NeutralSingleQuoteChar "' ＇ ’"
#define OpenSingleQuoteChar "` ｀ ‘"
#define CloseSingleQuoteChar "’"
#define NeutralDoubleQuoteChar "\" ＂ ”"
#define OpenDoubleQuoteChar "“"
#define CloseDoubleQuoteChar "”"

typedef enum { 
  LOAD_INIT, LOAD_CONTENT, LOAD_SPACE, LOAD_EOS, LOAD_QUOTE
} LoadStateType;

typedef enum {
  RSC_FILE, RSC_PSTR
} RSCType;

int LoadSentence(RSCType t, void *RSC, char *Sentence, int MaxLength)
{
  int i=0;
  int bSingleOpen=true, bDoubleOpen=true;
  char c[3]={0,};
  LoadStateType State=LOAD_INIT, LastState=LOAD_INIT;

  Sentence[0]=0;
  while (((t==RSC_FILE)?GetCharFromStream((FILE *)RSC, c):GetCharFromString((char **)RSC, c))) {
    if (strstr(SpaceChar, c)) {
      c[0]=' '; c[1]=0;
      if ((State==LOAD_INIT)||(State==LOAD_SPACE)) continue;
      if ((i>2)&&(State==LOAD_EOS)) break;
      if ((i>3)&&(State==LOAD_QUOTE)&&(LastState==LOAD_EOS)) {
        if (strcmp(Sentence+i-2, "‘")==0)
          strcpy(Sentence+i-2, "’");
        else if (strcmp(Sentence+i-2, "“")==0)
          strcpy(Sentence+i-2, "”");
        break;
      }
      LastState=State;
      State=LOAD_SPACE;
    }
    else if (strstr(EOSChar, c)) {
      LastState=State;
      State=LOAD_EOS;
    }
    else if (strstr(NeutralSingleQuoteChar, c)) {
      LastState=State;
      State=LOAD_QUOTE;
      if (bSingleOpen)
        strcpy(c, "'");
      else strcpy(c, "'");
      bSingleOpen=!bSingleOpen;
    }
    /*else if (strstr(OpenSingleQuoteChar, c)) {
      LastState=State;
      State=LOAD_QUOTE;
      strcpy(c, "‘");
      bSingleOpen=false;
    }
    else if (strstr(CloseSingleQuoteChar, c)) {
      LastState=State;
      State=LOAD_QUOTE;
      strcpy(c, "’");
      bSingleOpen=true;
    }*/
    else if (strstr(NeutralDoubleQuoteChar, c)) {
      LastState=State;
      State=LOAD_QUOTE;
      if (bDoubleOpen)
        strcpy(c, "\"");
      else strcpy(c, "\"");
      bDoubleOpen=!bDoubleOpen;
    }
    else if (strstr(OpenDoubleQuoteChar, c)) {
      LastState=State;
      State=LOAD_QUOTE;
      strcpy(c, "\"");
      bDoubleOpen=false;
    }
    else if (strstr(CloseDoubleQuoteChar, c)) {
      LastState=State;
      State=LOAD_QUOTE;
      strcpy(c, "\"");
      bDoubleOpen=true;
    }
    else {
      LastState=State;
      State=LOAD_CONTENT;
    }

    strcpy(Sentence+i, c);
    i+=strlen(c);
    if (i+3>=MaxLength) break;
  }

  return i>0;  
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadSentenceFromStream(FILE *f, char *Sentence, int MaxLength)
{

  return LoadSentence(RSC_FILE, f, Sentence, MaxLength);
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif 
int LoadSentenceFromString(char **pString, char *Sentence, int MaxLength)
{

  return LoadSentence(RSC_PSTR, pString, Sentence, MaxLength);
}

// HanTag 실행을 위한 사전 및 정보 읽기
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadHanTagEngine(const char *ProbEntryFilename, const char *ProbDataFilename)
{
  
  if (!CTagger::m_Rsc.Load(ProbEntryFilename, ProbDataFilename))
    return 0;
  return 1;
}

// 사전 및 정보를 위한 메모리 해제
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void EndHanTagEngine(void)
{
  CTagger::m_Rsc.UnLoad();
}

// HanTag class의 instance를 할당 받기
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void *CreateHanTag(void)
{
  CTagger *x=new CTagger;
  return x;
}

// HanTag class의 instance를 해제
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void FreeHanTag(void *HanTag)
{
  delete ((CTagger *)HanTag);
}

// 이미 할당 받은 HanTag의 instance를 이용하여 문장 형태소 분석 + 태깅을 수행
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoKomaAndHanTag(void *HanTag, TaggingMethod Method, char *Sentence, char *Wrd[MaxNumWrd], char *Result[MaxNumWrd][MaxNumAmb])
{
  CTagger *x=(CTagger *)HanTag;

  if (x==NULL) {
    Wrd[0]=NULL;
    Result[0][0]=NULL;
    return 0;
  }
  return x->DoTagging(Sentence, Wrd, Result, Method, 1);
}

// 이미 할당 받은 HanTag의 instance를 이용하여 한 어절을 형태소 분석 수행
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoHanTag(void *HanTag, TaggingMethod Method, char *Cnd[MaxNumWrd][MaxNumAmb], char *Result[MaxNumWrd][MaxNumAmb])
{
  CTagger *x=(CTagger *)HanTag;

  if (x==NULL) return 0;
  switch (Method) {
    case NO_TAGGING: 
      int ReturnValue;
      for (ReturnValue=0; Cnd[ReturnValue][0]; ReturnValue++);
      memcpy(Result, Cnd, sizeof(char *)*ReturnValue*MaxNumAmb);
      return ReturnValue;
    case PATH_BASED_TAGGING:
      return x->PathBasedTagging(Cnd, Result, 1);
    case STATE_BASED_TAGGING:
      return x->StateBasedTagging(Cnd, Result, 1);
  }

  Result[0][0]=NULL;
  return 0;
}
