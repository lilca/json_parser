#include "json_object.h"

JSONObject* JSONObject_new(void) {
    JSONObject* res = malloc(sizeof(JSONObject));
    JSONObject_init(res);
    return res;
}

void JSONObject_init(JSONObject* this) {
    this->maxSize = 0;
    this->size = 0;
    this->list = NULL;
    return;
}

void JSONObject_free(JSONObject* this) {
    if (this == NULL)
        return;
    if (this->list != NULL) {
        for (int idx = 0; idx < this->size; idx++) {
            if (this->list[idx] != NULL) {
                JSONKeyAndValue_free(this->list[idx]);
                this->list[idx] = NULL;
            }
        }
        free(this->list);
        this->list = NULL;
    }
    free(this);
    return;
}

void JSONObject_print(JSONObject* this, int depth) {
    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    printf("{\n");

    for (int idx = 0; idx < this->size; idx++) {
        JSONKeyAndValue_print(this->list[idx], depth + 1);
    }

    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    printf("}\n");
    return;
}

int JSONObject_parse(JSONObject* this, char** chr) {
    JSONKeyAndValue kv;
    JSONKeyAndValue_init(&kv);

    // Skip
    JSONCommon_skipChar(chr);
    if (**chr != '{')
          return FALSE;
    (*chr)++;
    // Skip
    JSONCommon_skipChar(chr);
    while (**chr != '}') {
        if (**chr == '\0') {
             return FALSE;
        } else if (JSONKeyAndValue_parse(&kv, chr)) {
            // Skip
            JSONCommon_skipChar(chr);
            if (!JSONObject_add(this, &kv)){
                return FALSE;
            }
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

int JSONObject_add(JSONObject* this, JSONKeyAndValue* kv) {
    if (this->maxSize < (this->size + 1) * sizeof(JSONKeyAndValue*) ) {
        this->maxSize += JSON_OBJECT_BLOCK * sizeof(JSONKeyAndValue*);
        JSONKeyAndValue** tmp = realloc(this->list, this->maxSize);

        if (tmp == NULL) {
            JSONObject_free(this);
            return FALSE;
        }
        this->list = tmp;
    }
    JSONKeyAndValue* tmp = JSONKeyAndValue_new();
    memcpy(tmp, kv, sizeof(JSONKeyAndValue));
    this->list[this->size] = tmp;
    this->size += 1;
    return TRUE;
}
