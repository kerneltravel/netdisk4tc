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
} DictEntry;

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
    DictEntry *first;
    size_t length;
} Dictionary;

//************************************
// Returns:   DICTIONARY *
// Description: �����µ��ֵ�
//************************************
Dictionary * dict_initialize(void);

//************************************
// Returns:   int���ɹ�ɾ������ DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS
// Description: ���ռ����Ƴ�ָ���ֵ���ض���Ŀ
//************************************
int dict_remove_element(Dictionary *, wchar_t *);

//************************************
// Returns:   size_t ����ָ��������Ŀ�Ĵ�С��δ���з��� 0
// Description: ���ռ�����ȡָ����Ŀ��С
//************************************
size_t dict_get_element_size(Dictionary *, wchar_t *);

//************************************
// Returns:   int �ɹ����� DICT_OK�������ļ���δ�ҵ��򷵻� DICT_MISS�����򷵻� DICT_FAILED
// Description: ���ռ�������ָ���ֵ���ض���Ŀ(ֱ������)
//************************************
int dict_get_element_s(Dictionary *, wchar_t *, const void **);

//************************************
// Returns:   void * ����ʹ�����Ӧ�ͷ�
// Description: ���ռ�������ָ���ֵ���ض���Ŀ�ĸ�����ʹ�ú�Ӧ�ͷ��ڴ档��������ڣ����� NULL
//************************************
void * dict_get_element(Dictionary *, wchar_t *);

//************************************
// Returns:   int
// Description: �ж��ֵ����Ƿ����ָ������
//************************************
int dict_exists(Dictionary *, wchar_t *);

//************************************
// Returns:   int �ɹ����� DICT_OK�����򷵻� DICT_FAILED
// Description: ���ռ�������ָ���ֵ���ض���Ŀ, ���ӵĲ���˵������ͷŸ��������ݣ�������������ݰ����༶�ķ����ڴ��Ϊ���ã�
//************************************
int dict_set_element_s(Dictionary *, wchar_t *, const void *, size_t, dict_destroyer);

//************************************
// Returns:   int �ɹ����� DICT_OK�����򷵻� DICT_FAILED
// Description: ���ռ�������ָ���ֵ���ض���Ŀ
//************************************
int dict_set_element(Dictionary *, wchar_t *, const void *, size_t);

//************************************
// Returns:   void
// Description: ����ָ�����ֵ䣬�ص������ķ���ֵָ���Ƿ���Ҫ��ֹ����
//************************************
void dict_traverse(const Dictionary *, dict_enumerator, void **);

//************************************
// Returns:   void
// Description: ����ָ�����ֵ�
//************************************
void dict_destroy(Dictionary **);
#endif