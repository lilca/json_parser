#ifndef JSONKEYANDVALUE_H
#define JSONKEYANDVALUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/typedefs.h>

#include "json_common.h"
#include "json_value.h"

struct _JSONKeyAndValue {
    JSONString* key;
    JSONValue* val;
};
typedef struct _JSONKeyAndValue JSONKeyAndValue;

JSONKeyAndValue* JSONKeyAndValue_new(void);
void JSONKeyAndValue_init(JSONKeyAndValue* this);
void JSONKeyAndValue_free(JSONKeyAndValue* this);
void JSONKeyAndValue_print(JSONKeyAndValue* this, int depth);
int JSONKeyAndValue_parse(JSONKeyAndValue* this, char** chr);

#endif