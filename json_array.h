#ifndef JSONARRAY_H
#define JSONARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/typedefs.h>

#include "json_value.h"

#define JSON_ARRAY_BLOCK 16

struct _JSONArray {
    uint32 maxSize;
    uint32 size;
    JSONValue** list;
};
typedef struct _JSONArray JSONArray;

JSONArray* JSONArray_new(void);
void JSONArray_init(JSONArray* this);
void JSONArray_free(JSONArray* this);
void JSONArray_print(JSONArray* this, int depth);
int JSONArray_parse(JSONArray* this, char** chr);

int JSONArray_add(JSONArray* this, JSONValue* val);

#endif