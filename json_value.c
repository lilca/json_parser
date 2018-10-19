#include "json_value.h"
#include "json_array.h"
#include "json_object.h"

static void _ptintWithDepth(JSONValueType type, int depth);

JSONValue* JSONValue_new(void) {
    JSONValue* res = malloc(sizeof(JSONValue));
    JSONValue_init(res);
    return res;
}

void JSONValue_init(JSONValue* this) {
    this->type = JSON_TYPE_EMPTY;
    this->val = NULL;
    return;
}

void JSONValue_free(JSONValue* this) {
    if (this == NULL)
        return;
    JSONValue_freeValue(this);
    free(this);
    return;
}

void JSONValue_freeValue(JSONValue* this) {
    if (this == NULL)
        return;
    switch (this->type) {
        case JSON_TYPE_STRING : JSONString_free(this->val); this->val = NULL; break;
        case JSON_TYPE_NUMBER : JSONNumber_free(this->val); this->val = NULL; break;
        case JSON_TYPE_OBJECT : JSONObject_free(this->val); this->val = NULL;break;
        case JSON_TYPE_ARRAY : JSONArray_free(this->val); this->val = NULL; break;
        case JSON_TYPE_TRUE :
        case JSON_TYPE_FALSE :
        case JSON_TYPE_NULL :
        default : break;
    }
   return;
}

void JSONValue_print(JSONValue* this, int depth) {
    if (this == NULL)
        return;
    switch (this->type) {
        case JSON_TYPE_STRING : JSONString_print(this->val, depth); break;
        case JSON_TYPE_NUMBER : JSONNumber_print(this->val, depth); break;
        case JSON_TYPE_OBJECT : JSONObject_print(this->val, depth); break;
        case JSON_TYPE_ARRAY : JSONArray_print(this->val, depth); break;
        case JSON_TYPE_TRUE : _ptintWithDepth(JSON_TYPE_TRUE, depth); break;
        case JSON_TYPE_FALSE : _ptintWithDepth(JSON_TYPE_FALSE, depth); break;
        case JSON_TYPE_NULL : _ptintWithDepth(JSON_TYPE_NULL, depth); break;
        default : _ptintWithDepth(-1, depth); break;
    }
    return;
}

static void _ptintWithDepth(JSONValueType type, int depth) {
    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    switch (type) {
        case JSON_TYPE_TRUE : printf("true\n"); break;
        case JSON_TYPE_FALSE : printf("false\n"); break;
        case JSON_TYPE_NULL : printf("null\n"); break;
        default : printf("unknown value\n"); break;
    }
    return;
}

int JSONValue_parse(JSONValue* this, char** chr) {
    JSONNumber num;
    JSONString str;
    JSONArray array;
    JSONObject object;
    JSONNumber_init(&num);
    JSONString_init(&str);
    JSONArray_init(&array);
    JSONObject_init(&object);

    // Skip
    JSONCommon_skipChar(chr);

    if (JSONString_parse(&str, chr)) {
        JSONString* tmp = JSONString_new();
        memcpy(tmp, &str, sizeof(JSONString));
        this->type = JSON_TYPE_STRING;
        this->val = tmp;
    } else if (JSONNumber_parse(&num, chr)) {
        JSONNumber* tmp = JSONNumber_new();
        memcpy(tmp, &num, sizeof(JSONNumber));
        this->type = JSON_TYPE_NUMBER;
        this->val = tmp;
    } else if (JSONObject_parse(&object, chr)) {
        JSONObject* tmp = JSONObject_new();
        memcpy(tmp, &object, sizeof(JSONObject));
        this->type = JSON_TYPE_OBJECT;
        this->val = tmp;
    } else if (JSONArray_parse(&array, chr)) {
        JSONArray* tmp = JSONArray_new();
        memcpy(tmp, &array, sizeof(JSONArray));
        this->type = JSON_TYPE_ARRAY;
        this->val = tmp;
    } else if (strncmp(*chr, "true", 4) == 0){
        this->type = JSON_TYPE_TRUE;
        *chr += 4;
    } else if (strncmp(*chr, "false", 5) == 0){
        this->type = JSON_TYPE_FALSE;
        *chr += 5;
    } else if (strncmp(*chr, "null", 4) == 0){
        this->type = JSON_TYPE_NULL;
        *chr += 4;
    } else {
        return FALSE;
    }
    return TRUE;
}
