#include "json_array.h"

JSONArray* JSONArray_new(void) {
    JSONArray* res = malloc(sizeof(JSONArray));
    JSONArray_init(res);
    return res;
}

void JSONArray_init(JSONArray* this) {
    this->maxSize = 0;
    this->size = 0;
    this->list = NULL;
    return;
}

void JSONArray_free(JSONArray* this) {
    if (this == NULL)
        return;
    if (this->list != NULL) {
        for (int idx = 0; idx < this->size; idx++) {
            if (this->list[idx] != NULL) {
                JSONValue_free(this->list[idx]);
                this->list[idx] = NULL;
            }
        }
        free(this->list);
        this->list = NULL;
    }
    free(this);
    return;
}

void JSONArray_print(JSONArray* this, int depth) {
    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    printf("[\n");

    for (int idx = 0; idx < this->size; idx++)
        JSONValue_print(this->list[idx], depth + 1);

    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    printf("]\n");
    return;
}

int JSONArray_parse(JSONArray* this, char** chr) {
    JSONValue val;
    JSONValue_init(&val);

    // Skip
    JSONCommon_skipChar(chr);

    if (**chr != '[')
          return FALSE;
    (*chr)++;
    while (**chr != ']') {
        if (**chr == '\0') {
             return FALSE;
        } else if (JSONValue_parse(&val, chr)) {
            // Skip
            JSONCommon_skipChar(chr);
            JSONArray_add(this, &val);
            if (**chr == ',') {
                (*chr)++;
                continue;
            } else
                continue;
        }
        return FALSE;
    }
    (*chr)++;
    return TRUE;
}

int JSONArray_add(JSONArray* this, JSONValue* val) {
    if (this->maxSize < (this->size + 1) * sizeof(JSONValue*) ) {
        this->maxSize += JSON_ARRAY_BLOCK * sizeof(JSONValue*);
        JSONValue** tmp = realloc(this->list, this->maxSize);
        if (tmp == NULL) {
            JSONArray_free(this);
            return FALSE;
        }
        this->list = tmp;
    }
    JSONValue* tmp = JSONValue_new();
    memcpy(tmp, val, sizeof(JSONValue));
    this->list[this->size] = tmp;
    this->size += 1;
    return TRUE;
}
