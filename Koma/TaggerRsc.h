// TaggerRsc.h: interface for the CTaggerRsc class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __TAGGERRSC__
#define __TAGGERRSC__

#include "nlp.def"
#include "FST.h"

#define e 0.000001

class CTaggerRsc  
{
public:
  CTaggerRsc();
  virtual ~CTaggerRsc();
  bool IsValid();
  bool Load(const char *ProbEntryFilename, const char *ProbDataFilename);
  bool ReLoad(const char *ProbEntryFilename, const char *ProbDataFilename);
  bool UnLoad();
  double GetPrbWrd(char *Anl);
  double GetPrbTrn(char *PrevAnal, char *CurrAnal);
  double GetPrbMrp(char *Key);
  double GetPrbPos2gram(char *Key);
private:
  bool m_bValid;

  FST *m_Entry;
  int m_nEntry;
  double *m_Prob;
};

#endif 
