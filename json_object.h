#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/typedefs.h>

#include "json_common.h"
#include "json_keyandvalue.h"

#define JSON_OBJECT_BLOCK 16

struct _JSONObject {
    uint32 maxSize;
    uint32 size;
    JSONKeyAndValue** list;
};
typedef struct _JSONObject JSONObject;

JSONObject* JSONObject_new(void);
void JSONObject_init(JSONObject* this);
void JSONObject_free(JSONObject* this);
void JSONObject_print(JSONObject* this, int depth);
int JSONObject_parse(JSONObject* this, char** chr);

int JSONObject_add(JSONObject* this, JSONKeyAndValue* kv);

#endif