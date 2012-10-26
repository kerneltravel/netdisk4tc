#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <stdlib.h>
#include <Windows.h>

typedef struct _pair {
	WCHAR *key;
	void *value;
	struct _pair *previous;
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
typedef INT (*DictionaryEnumerator)(WCHAR *, void *);

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
DICTIONARY * InitializeDictionary(void);

//************************************
// Method:    DictionaryRemoveElement
// FullName:  DictionaryRemoveElement
// Access:    public 
// Returns:   void *����������ļ���δ�ҵ��򷵻�NULL��������ֵ���ɾ��������������Ŀ��������ָ�����Ŀ��ָ��
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: WCHAR *
// Description: ���ռ����Ƴ�ָ���ֵ���ض���Ŀ
//************************************
void * DictionaryRemoveElement(DICTIONARY *, WCHAR *);

//************************************
// Method:    DictionaryGetElement
// FullName:  DictionaryGetElement
// Access:    public 
// Returns:   void *
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: WCHAR *
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
void * DictionaryGetElement(DICTIONARY *, WCHAR *);

//************************************
// Method:    DictionarySetElement
// FullName:  DictionarySetElement
// Access:    public 
// Returns:   void *����������ļ���δ�ҵ��򷵻�NULL��������ֵ��и��¸�����������Ŀ��������ָ�����Ŀԭʼ��ֵ
// Qualifier:
// Parameter: DICTIONARY *
// Parameter: WCHAR *
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
void * DictionarySetElement(DICTIONARY *, WCHAR *, void *);

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
void DictionaryTraverse(const DICTIONARY *, DictionaryEnumerator);

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
void FreeDictionary(DICTIONARY *, int);

#endif