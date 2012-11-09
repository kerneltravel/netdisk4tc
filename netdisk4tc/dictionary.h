#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "utility.h"

#define DICT_OK 0
#define DICT_FATAL 1
#define DICT_MISS 2

typedef void (*dict_destroyer)(void **);

typedef struct _pair {
    wchar_t *key;
    size_t size;
    void *value;
    dict_destroyer destroyer;
    struct _pair *next;
} DICTPAIR;

//************************************
// Method:    DictionaryEnumerator
// FullName:  DictionaryEnumerator
// Access:    public 
// Returns:   INT��������� 0 ����ֹ����������ֵ����
// Parameter: (WCHAR *, void *)
// Description: ���ֵ����ʱ�ĵ����ص�������4������ָ������, ��ֵ, ֵ�Ĵ�С���Զ�������
//************************************
typedef int (*dict_enumerator)(const wchar_t *, const void *, size_t size, void **);

typedef struct _dictionary {
    DICTPAIR *first;
    size_t length;
} DICTIONARY;

//************************************
// Returns:   DICTIONARY *
// Description: �����µ��ֵ�
//************************************
DICTIONARY * dict_initialize(void);

//************************************
// Returns:   int���ɹ�ɾ������ DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS
// Description: ���ռ����Ƴ�ָ���ֵ���ض���Ŀ
//************************************
int dict_remove_element(DICTIONARY *, wchar_t *);

//************************************
// Returns:   size_t ����ָ��������Ŀ�Ĵ�С��δ���з��� 0
// Description: ���ռ�����ȡָ����Ŀ��С
//************************************
size_t dict_get_element_size(DICTIONARY *, wchar_t *);

//************************************
// Returns:   int �ɹ����� DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS�����򷵻� DICT_FAILED
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
int dict_get_element_s(DICTIONARY *, wchar_t *, void **, size_t);

//************************************
// Returns:   void * ����ʹ�����Ӧ�ͷ�
// Description: ���ռ�������ָ���ֵ���ض���Ŀ��ʹ�ú�Ӧ�ͷ��ڴ档��������ڣ����� NULL
//************************************
void * dict_get_element(DICTIONARY *, wchar_t *);

//************************************
// Returns:   int
// Description: �ж��ֵ����Ƿ����ָ������
//************************************
int dict_exists(DICTIONARY *, wchar_t *);

//************************************
// Returns:   int �ɹ����� DICT_OK�����򷵻� DICT_FAILED
// Description: ���ռ�������ָ���ֵ���ض���Ŀ, ���ӵĲ���˵������ͷŸ��������ݣ�������������ݰ����༶�ķ����ڴ��Ϊ���ã�
//************************************
int dict_set_element_s(DICTIONARY *, wchar_t *, const void *, size_t, dict_destroyer);

//************************************
// Returns:   int �ɹ����� DICT_OK�����򷵻� DICT_FAILED
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
int dict_set_element(DICTIONARY *, wchar_t *, const void *, size_t);

//************************************
// Returns:   void
// Description: ����ָ�����ֵ䣬�ص������ķ���ֵָ���Ƿ���Ҫ��ֹ����
//************************************
void dict_traverse(const DICTIONARY *, dict_enumerator, void **);

//************************************
// Returns:   void
// Description: ����ָ�����ֵ�
//************************************
void dict_destroy(DICTIONARY **);
#endif