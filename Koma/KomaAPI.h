#ifndef __MorphAPI__
#define __MorphAPI__

#include "nlp.def"

// Koma ������ ���� ���� �� ���� �б�
// ��ȯ�� : 1 - ����, 0 - ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int LoadKomaEngine(const char *MainEntryFilename, const char *MainDataFilename,
                    const char *ConnectionTableFilename,
                    const char *TagFilename, const char *TagOutFilename);

// ���� �� ������ ���� �޸� ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void EndKomaEngine(void);

/* CodeType   -   1: KS5601 code, 0: TRIGEM code */

// Koma class�� instance�� �Ҵ� �ޱ�
// ��ȯ�� : NULL - ����, ��Ÿ - ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void *CreateKoma(int CodeType);

// Koma class�� instance�� ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
void FreeKoma(void *Koma);

// �̹� �Ҵ� ���� Koma�� instance�� �̿��Ͽ� �� ������ ���¼� �м� ����
// ��ȯ�� : 1 - ����, 0 - ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoKomaOneWord(void *Koma, char *Eojeol, char Result[MaxNumAmb][BuffSize]);

// �̹� �Ҵ� ���� Koma�� instance�� �̿��Ͽ� �� ������ ���¼� �м� ����
// ��ȯ�� : ���峻 ���� ����
// ���� : �� �Լ��� �°ſ��� ����ϱ� ���� ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
int DoKomaOneSentence(void *Koma, char *Sentence, void *Result);

// ���¼� �м� ��� ���ٿ� �Լ�

// ���¼� �м� ��� ����
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
short GetNumResult(void *Koma);

// wai��° �м� ����� wcol��° ���¼��� �ε��� ��������
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
short GetPair(void *Koma, short wai, short wcol);

// pi��° �ε����� �ش��ϴ� ���¼��� ���ڿ�
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
const char *GetMorph(void *Koma, short pi);

// pi��° �ε����� �ش��ϴ� ���¼��� ǰ��
#ifdef WIN32
extern "C" __declspec(dllexport) 
#endif
const char *GetTag(void *Koma, short pi);

#endif
