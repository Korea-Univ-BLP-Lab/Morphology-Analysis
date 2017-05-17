// TaggerRsc.cpp: implementation of the CTaggerRsc class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TaggerRsc.h"
#include "nlp.def"
#include "Taganal.h"

#define MaxCurrMrp 2000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#define ProbDataSize 15

CTaggerRsc::CTaggerRsc()
{
  m_bValid=false;
  m_Entry=NULL;
  m_Prob=NULL;
}

CTaggerRsc::~CTaggerRsc()
{
  UnLoad();
}

bool CTaggerRsc::IsValid()
{
  return m_bValid;
}

bool CTaggerRsc::Load(const char *ProbEntryFilename, const char *ProbDataFilename)
{
  FILE *f;
  int i;

  if (m_bValid) return true;

  if ((m_Entry=LoadFST(ProbEntryFilename))==NULL) return false;
  if ((f=fopen(ProbDataFilename, "rb"))==NULL) return false;
  m_nEntry=GetNumberOfEntry(m_Entry);
  if ((m_Prob=(double *)malloc(sizeof(double)*m_nEntry))==NULL) 
    return false;
  for (i=0; i<m_nEntry; i++) 
    fscanf(f, "%le", m_Prob+i);
  fclose(f);

  m_bValid=true;
  return true;

}

bool CTaggerRsc::UnLoad()
{
  if (!m_bValid) return false;
  if (m_Entry) free(m_Entry);
  if (m_Prob) free(m_Prob);
  m_bValid=false;
  return true;
}

bool CTaggerRsc::ReLoad(const char *ProbEntryFilename, const char *ProbDataFilename)
{

  UnLoad();
  return Load(ProbEntryFilename, ProbDataFilename);
}

double CTaggerRsc::GetPrbMrp(char *Key) 
{
  int Index=String2Hash(m_Entry, Key);

  if (Index==NULL_INDEX) 
    return e;
  else return m_Prob[Index];
} /* GetPrbMrp */

double CTaggerRsc::GetPrbPos2gram(char *Key) 
{
  int Index=String2Hash(m_Entry, Key);
  if (Index==NULL_INDEX) 
    return e;
  else return m_Prob[Index];
} /* GetPrbPos2gram */

/*=====================================================*\
  Wrd�� �߻� Ȯ���� ���Ѵ�.
\*=====================================================*/

double CTaggerRsc::GetPrbWrd (char *Anl) 
{
  int NumMrp;
  double PrbWrd;
  char *Last;
  char *Res;
  char Buffer[BuffSize];
  char UnkTag[5];
  int LenStr;
  int i;

  char CurrMrp[MaxCurrMrp], CurrPos[MaxLenPos], PrevPos[MaxLenPos];
  char MrpPos[MaxCurrMrp+MaxLenPos+1], Pos2gram[MaxLenPos*2+1];

  /* �м� ����� ���� ��� */
  if (Anl==NULL) 
    return e;

  LenStr=strlen(Anl);
  for(i=0;i<4;i++)
    UnkTag[i] = Anl[LenStr-4+i];
  UnkTag[i]=NULL;

  if (strcmp(UnkTag,"/UNK")==0)
  {
      for(i=0;i<4;i++)
          UnkTag[i]=UnkTag[i+1];      
      for(i=0;i<LenStr-4;i++)
          CurrMrp[i] = Anl[i];
      CurrMrp[i] = NULL;      
      
      strcpy(CurrPos, UnkTag);

      sprintf(MrpPos, "%s%s%s", CurrMrp, MrpTagMark, CurrPos);
      if (NumMrp==0) 
	    PrbWrd=GetPrbMrp(MrpPos);
      else {
	    /* ���� ����Ȯ���� ���ϱ� ���� Ű�� �����. */
        sprintf(Pos2gram, "%s%s%s", PrevPos, MrpConMark, CurrPos);
	    PrbWrd*=GetPrbPos2gram(Pos2gram)*GetPrbMrp(MrpPos);
      } /* else ... if */
      strcpy(PrevPos, CurrPos);

      return PrbWrd;
  }
  
  strcpy(Buffer, Anl);
  /* PrbWrd�� ��� */
  for (Res=anltok_r(Buffer, &Last), NumMrp=0; Res!=NULL; Res=anltok_r(NULL, &Last), NumMrp++) {
    /* ������ ���¼Ҹ� �о�´�. */
    if (strlen(Res)>MaxLenMrp-1) return e;
    strcpy(CurrMrp, Res);
    /* ������ ǰ�縦 �о�´�. */
    if ((Res=anltok_r(NULL, &Last))==NULL) return e;
    if (strlen(Res)>MaxLenPos-1) return e;
    strcpy(CurrPos, Res);

    /* ���¼� �߻�Ȯ���� ���ϱ� ���� Ű�� �����. */
    sprintf(MrpPos, "%s%s%s", CurrMrp, MrpTagMark, CurrPos);
    if (NumMrp==0) 
	    PrbWrd=GetPrbMrp(MrpPos);
    else {
	    /* ���� ����Ȯ���� ���ϱ� ���� Ű�� �����. */
      sprintf(Pos2gram, "%s%s%s", PrevPos, MrpConMark, CurrPos);
	    PrbWrd*=GetPrbPos2gram(Pos2gram)*GetPrbMrp(MrpPos);
    } /* else ... if */
    strcpy(PrevPos, CurrPos);
  } /* for (CurrPair) */

  return PrbWrd;
} /* GetPrbWrd */

/*=====================================================*\
  Wrd�� ǰ�翭 ���� Ȯ���� ���Ѵ�.
\*=====================================================*/
double CTaggerRsc::GetPrbTrn (char *PrevAnal, char *CurrAnal) 
{
  char Pos2gram[MaxLenPos*2+1];
  char PrevTail[MaxLenPos];
  char CurrHead[MaxLenPos];

  /* �ܺ� ����Ȯ���� ���ϱ� ���� Ű�� �����. */
  GetPosTail(PrevAnal, PrevTail);
  GetPosHead(CurrAnal, CurrHead);

  sprintf(Pos2gram, "%s%s%s", PrevTail, WrdConMark, CurrHead);

  return GetPrbPos2gram(Pos2gram);
} /* GetPrbTrn */
