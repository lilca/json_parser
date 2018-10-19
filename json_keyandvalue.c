#include "json_keyandvalue.h"

JSONKeyAndValue* JSONKeyAndValue_new(void) {
    JSONKeyAndValue* res = malloc(sizeof(JSONKeyAndValue));
    JSONKeyAndValue_init(res);
    return res;
}

void JSONKeyAndValue_init(JSONKeyAndValue* this) {
    this->key = NULL;
    this->val = NULL;
    return;
}

void JSONKeyAndValue_free(JSONKeyAndValue* this) {
    if (this == NULL)
        return;
    if (this->key != NULL) {
        JSONString_free(this->key);
        this->key = NULL;
    }
    if (this->val != NULL) {
        JSONValue_free(this->val);
        this->val = NULL;
    }
    free(this);
    return;
}

void JSONKeyAndValue_print(JSONKeyAndValue* this, int depth) {
    if (this == NULL)
        return;

    JSONString_print(this->key, depth + 1);
    for (int idx = 0; idx < depth + 1; idx++)
        printf(" ");
    printf(" :\n");
    JSONValue_print(this->val, depth + 1);

    return;
}

int JSONKeyAndValue_parse(JSONKeyAndValue* this, char** chr) {
    JSONString key;
    JSONString_init(&key);
    JSONValue val;
    JSONValue_init(&val);

    // Skip
    JSONCommon_skipChar(chr);

    // for KEY
    if (JSONString_parse(&key, chr)) {
        JSONString* tmp = JSONString_new();
        memcpy(tmp, &key, sizeof(JSONString));
        this->key = tmp;
    } else {
        return FALSE;
    }
    // Skip
    JSONCommon_skipChar(chr);
    // CHeck ':'
    if (**chr != ':')
        return FALSE;
    (*chr)++;
    // for VALUE
    if (JSONValue_parse(&val, chr)) {
        JSONValue* tmp = JSONValue_new();
        memcpy(tmp, &val, sizeof(JSONValue));
        this->val = tmp;
    } else {
        JSONString_freeString(&key);
        return FALSE;
    }
    return TRUE;
}
