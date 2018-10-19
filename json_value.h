#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/typedefs.h>

#include "json_common.h"
#include "json_number.h"
#include "json_string.h"

enum _JSONValueType {
    JSON_TYPE_STRING,
    JSON_TYPE_NUMBER,
    JSON_TYPE_OBJECT,
    JSON_TYPE_ARRAY,
    JSON_TYPE_TRUE,
    JSON_TYPE_FALSE,
    JSON_TYPE_NULL,
    JSON_TYPE_EMPTY = -1
};
typedef enum _JSONValueType JSONValueType;

struct _JSONValue {
    JSONValueType type;
    void* val;
};
typedef struct _JSONValue JSONValue;

JSONValue* JSONValue_new(void);
void JSONValue_init(JSONValue* this);
void JSONValue_free(JSONValue* this);
void JSONValue_freeValue(JSONValue* this);
void JSONValue_print(JSONValue* this, int depth);
int JSONValue_parse(JSONValue* this, char** chr);

#endif