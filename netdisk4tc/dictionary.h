#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define DICT_OK 0
#define DICT_FAILED 1
#define DICT_MISS 2

typedef struct _pair {
	wchar_t *key;
	void *value;
	size_t *size;
	struct _pair *next;
} DICTPAIR;

//************************************
// Method:    DictionaryEnumerator
// FullName:  DictionaryEnumerator
// Access:    public 
// Returns:   INT��������� 0 ����ֹ����������ֵ����
// Parameter: (WCHAR *, void *)
// Description: ���ֵ����ʱ�ĵ����ص�������2������ָ����������ֵ
//************************************
typedef int (*DictEnumerator)(wchar_t *, void *);

typedef struct _dictionary{
	DICTPAIR *first;
	DICTPAIR *last;
	unsigned int length;
} DICTIONARY;

//************************************
// Method:    InitializeDictionary
// FullName:  InitializeDictionary
// Access:    public 
// Returns:   DICTIONARY *
// Qualifier:
// Parameter: void
// Description: �����µ��ֵ�
//************************************
DICTIONARY * InitializeDict(void);

//************************************
// Method:    DictionaryRemoveElement
// FullName:  DictionaryRemoveElement
// Access:    public 
// Returns:   int���ɹ�ɾ������ DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS�����򷵻� DICT_FAILED
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: WCHAR *
// Description: ���ռ����Ƴ�ָ���ֵ���ض���Ŀ
//************************************
int DictRemoveElement(DICTIONARY *, wchar_t *);

//************************************
// Method:    DictGetElementSize
// FullName:  DictGetElementSize
// Access:    public 
// Returns:   size_t
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: wchar_t *
// Description: ���ռ�����ȡָ����Ŀ��С
//************************************
size_t DictGetElementSize(DICTIONARY *, wchar_t *);

//************************************
// Method:    DictionaryGetElement
// FullName:  DictionaryGetElement
// Access:    public 
// Returns:   int �ɹ����� DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS�����򷵻� DICT_FAILED
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: wchar_t *
// Parameter: void * * 
// Parameter: size_t
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
int DictGetElementS(DICTIONARY *, wchar_t *, void **, size_t);

//************************************
// Method:    DictGetElement
// FullName:  DictGetElement
// Access:    public 
// Returns:   void *
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: wchar_t *
// Description: ���ռ�������ָ���ֵ���ض���Ŀ��ʹ�ú�Ӧ�ͷ��ڴ档��������ڣ����� NULL
//************************************
void * DictGetElement(DICTIONARY *, wchar_t *);

//************************************
// Method:    DictionarySetElement
// FullName:  DictionarySetElement
// Access:    public 
// Returns:   int �ɹ����� DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS�����򷵻� DICT_FAILED
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: WCHAR *
// Parameter: const void *
// Parameter: size_t
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
int DictSetElement(DICTIONARY *, wchar_t *, const void *, size_t);

//************************************
// Method:    DictionaryTraverse
// FullName:  DictionaryTraverse
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const DICTIONARY *
// Parameter: DictionaryEnumerator
// Description: ����ָ�����ֵ䣬�ص������ķ���ֵָ���Ƿ���Ҫ��ֹ����
//************************************
void DictTraverse(const DICTIONARY *, DictEnumerator);

//************************************
// Method:    FreeDictionary
// FullName:  FreeDictionary
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: BOOL �Ƿ�Ҫͬʱ����ָ����Ŀ��ָ�루��Щ���ݲ������ֵ������������������ر����ף�����Ҫѡ�񽫴˲�������ΪTRUE
// Description: ����ָ�����ֵ�
//************************************
void FreeDict(DICTIONARY *);

#endif