#include "dictionary.h"


Dictionary * dict_initialize(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    memset(dict, 0, sizeof(Dictionary));
    dict->first = NULL;
    dict->length = 0;
    return dict;
}

int dict_set_element_s(Dictionary *pdict, wchar_t *key, const void *value, size_t size, dict_destroyer destroyer) {
    void *ret = NULL;
    DictEntry *iter, *node = NULL;
    iter = pdict->first;
    while(iter != NULL) {
        if(wcscmp(key, iter->key) == 0) {
            node = iter;
        }
        if(iter->next == NULL) {
            break;
        }
        iter = iter->next;
    }
    if(node != NULL) {
        if(iter->destroyer) {
            iter->destroyer(&iter->value);
        } else {
            free(iter->value);
        }
        iter->value = malloc(size);
        if(!iter->value) {
            return DICT_FATAL;
        }
        memcpy(iter->value, value, size);
        iter->size = size;
        return DICT_OK;
    } else {
        node = (DictEntry*)malloc(sizeof(DictEntry));
        memset(node, 0, sizeof(DictEntry));
        node->key = _wcsdup(key);
        if(!node->key) {
            return DICT_FATAL;
        }
        node->value = malloc(size);
        if(!node->value) {
            return DICT_FATAL;
        }
        memset(node->value, 0, size);
        memcpy(node->value, value, size);
        node->destroyer = destroyer;
        node->size = size;
        node->next = NULL;
        if(iter) {
            iter->next = node;
        } else {
            pdict->first = node;
        }
        pdict->length++;
        return DICT_OK;
    }
}

int dict_set_element(Dictionary *pdict, wchar_t *key, const void *value, size_t size) {
    return dict_set_element_s(pdict, key, value, size, NULL);
}

int dict_get_element_s(Dictionary *pdict, wchar_t *key, const void **value) {
    DictEntry *iter = pdict->first;
    while(iter != NULL) {
        if(wcscmp(key, iter->key) == 0) {
            *value = iter->value;
            return DICT_OK;
        }
        iter = iter->next;
    }
    return DICT_MISS;
}

void * dict_get_element(Dictionary *pdict, wchar_t *key) {
    void *ret = NULL;
    DictEntry *iter = pdict->first;
    while(iter != NULL) {
        if(wcscmp(key, iter->key) == 0) {
            ret = malloc(iter->size);
            if(!ret) {
                return NULL;
            }
            memcpy(ret, iter->value, iter->size);
            return ret;
        }
        iter = iter->next;
    }
    return NULL;
}

int dict_exists(Dictionary *pdict, wchar_t *key) {
    DictEntry *iter = pdict->first;
    while(iter != NULL) {
        if(wcscmp(key, iter->key) == 0) {
            return TRUE;
        }
        iter = iter->next;
    }
    return FALSE;
}

int dict_remove_element(Dictionary *pdict, wchar_t *key) {
    DictEntry *iter = pdict->first, *hit = NULL;
    while(iter != NULL) {
        if(pdict->first == iter && wcscmp(key, iter->key) == 0) {
            pdict->first = iter->next;
            hit = iter;
            break;
        }
        if(iter->next != NULL && wcscmp(key, iter->next->key) == 0) {
            hit = iter->next;
            iter->next = iter->next->next;
            break;
        }
        iter = iter->next;
    }
    if(hit) {
        free(hit->key);
        if(hit->destroyer) {
            hit->destroyer(&hit->value);
        } else {
            free(hit->value);
        }
        free(hit);
        pdict->length--;
        return DICT_OK;
    }
    return DICT_MISS;
}

void dict_traverse(const Dictionary *pdict, dict_enumerator enumerator, void **data) {
    DictEntry *node = pdict->first;
    while(node != NULL) {
        if(!enumerator(node->key, node->value, node->size, data)) {
            break;
        }
        node = node->next;
    }
}

void dict_destroy(Dictionary **pdict) {
    DictEntry *iter = (*pdict)->first, *tmp;
    while(iter != NULL) {
        tmp = iter;
        iter = iter->next;
        free(tmp->key);
        if(tmp->destroyer) {
            tmp->destroyer(&tmp->value);
        } else {
            free(tmp->value);
        }
    }
    free(*pdict);
    *pdict = NULL;
}

size_t dict_get_element_size(Dictionary *pdict, wchar_t *key) {
    DictEntry *iter = pdict->first;
    while(iter != NULL) {
        if(wcscmp(key, iter->key) == 0) {
            return iter->size;
        }
        iter = iter->next;
    }
    return 0;
}