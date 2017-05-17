#ifndef __HANTAGAPI__
#define __HANTAGAPI__

#include "nlp.def"

#ifndef __TaggingMethod__
#define __TaggingMethod__
typedef enum {
  NO_TAGGING,           // ���¼� �м���
  PATH_BASED_TAGGING,   // ��� ��� �±�
  STATE_BASED_TAGGING   // ���� ��� �±�
} TaggingMethod;
#endif

// ���Ͽ��� �� ������ �о���̱�
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadSentenceFromStream(FILE *f, char *Sentence, int MaxLength);

// ��Ʈ��(*pString)���� �� ������ �о���̱�
// ������ ���� �� *pString�� ���� ���� ������ ���� ��ġ�� �Ű���
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadSentenceFromString(char **pString, char *Sentence, int MaxLength);

// HanTag ������ ���� ���� �� ���� �б�
// ��ȯ�� : 1 - ����, 0 - ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadHanTagEngine(const char *ProbEntryFilename, const char *ProbDataFilename);

// ���� �� ������ ���� �޸� ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void EndHanTagEngine(void);

// HanTag class�� instance�� �Ҵ� �ޱ�
// ��ȯ�� : NULL - ����, ��Ÿ - ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void *CreateHanTag(void);

// HanTag class�� instance�� ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void FreeHanTag(void *HanTag);

// �̹� �Ҵ� ���� HanTag�� instance�� �̿��Ͽ� �� ������ ���¼� �м� �� �±�
// ��ȯ�� : ���峻 ������ ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoKomaAndHanTag(void *HanTag, TaggingMethod Method, char *Sentence, char *Wrd[MaxNumWrd], char *Result[MaxNumWrd][MaxNumAmb]);

// �̹� �Ҵ� ���� HanTag�� instance�� �̿��Ͽ� �� ������ ���¼� �м� �� �±�
// ��ȯ�� : ���峻 ������ ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoHanTag(void *HanTag, TaggingMethod Method, char *Cnd[MaxNumWrd][MaxNumAmb], char *Result[MaxNumWrd][MaxNumAmb]);

#endif
