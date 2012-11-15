#ifndef DISKS_H_
#define DISKS_H_
#include <stdlib.h>
#include "dictionary.h"
#include "lua/lauxlib.h"

#define NDISK_OK 0
#define NDISK_FATAL 1

typedef struct _ndisk_entry {
    wchar_t * name;
    wchar_t * description;
    wchar_t * signin;
    lua_State *script;
} NDiskEntry;

extern NDiskEntry *available_disk_entries;
extern size_t available_disk_entries_length;
extern Dictionary *available_disks;

typedef struct _disk{
    wchar_t * type;
    wchar_t * username;
    wchar_t * password;
    wchar_t * nickname;
    wchar_t * token;
    wchar_t * secret;
} NDisk;

void ndisk_destroy(NDisk **);
void ndisks_save(void);
void ndisks_load(void);

//************************************
// Returns:   int���ɹ�ɾ������ NDISK_OK, ����ʧ�ܷ��� NDISK_FATAL
// Description: �������·��, ��ö�Ӧ�� ���� ���ͺ� ����
//************************************
int ndisk_parse(const wchar_t *, NDiskEntry **entry, NDisk **, wchar_t *);

//************************************
// Returns:   int���ɹ�ɾ������ NDISK_OK, ����ʧ�ܷ��� NDISK_FATAL
// Description: ��ȡָ������ָ��Ŀ¼���ļ��б�
//************************************
int ndisk_dir(Dictionary *, const NDiskEntry *, NDisk *, const wchar_t *);
#endif