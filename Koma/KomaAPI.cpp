#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Koma.h"

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadKomaEngine(const char *MainEntryFilename, const char *MainDataFilename,
                    const char *ConnectionTableFilename,
                    const char *TagFilename, const char *TagOutFilename)
{

  if (!CKoma::m_Rsc.Load(MainEntryFilename, MainDataFilename, ConnectionTableFilename, TagFilename, TagOutFilename))
    return 0;
  return 1;
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void EndKomaEngine(void)
{
  CKoma::m_Rsc.UnLoad();
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void *CreateKoma(int CodeType)
{
  CKoma *x=new CKoma;
  if (x!=NULL) x->m_HcodeType=CodeType;
  return x;
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void FreeKoma(void *Koma)
{

  delete ((CKoma *)Koma);
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoKomaOneWord(void *Koma, char *Eojeol, char Result[MaxNumAmb][BuffSize])
{

  if (Koma==NULL) return 0;
  return ((CKoma *)Koma)->AnalyzeWord(Eojeol, Result);
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoKomaOneSentence(void *Koma, char *Sentence, void *Result)
{

  if (Koma==NULL) return 0;
  return ((CKoma *)Koma)->AnalyzeSentence(Sentence, (KomaResultType *)Result);
}

#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int GetNumResult(void *Koma)
{
  if (Koma==NULL) return 0;
  return ((CKoma *)Koma)->GetNumResult();
}

// wai번째 분석 결과의 wcol번째 형태소의 인덱스 가져오기
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int GetPair(void *Koma, short wai, short wcol)
{
  if (Koma==NULL) return 0;
  return ((CKoma *)Koma)->GetPair(wai, wcol);
}

// pi번째 인덱스에 해당하는 형태소의 문자열
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
const char *GetMorph(void *Koma, short pi)
{
  if (Koma==NULL) return NULL;
  return ((CKoma *)Koma)->GetMorph(pi);
}
// pi번째 인덱스에 해당하는 형태소의 품사
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
const char *GetTag(void *Koma, short pi)
{
  if (Koma==NULL) return NULL;
  return ((CKoma *)Koma)->GetTag(pi);
}
