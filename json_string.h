#ifndef JSONSTRING_H
#define JSONSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/typedefs.h>

#include "json_common.h"

#define JSON_STRING_BLOCK 4096

struct _JSONString {
    uint32 size;
    uint8* buf;
};
typedef struct _JSONString JSONString;

JSONString* JSONString_new(void);
void JSONString_init(JSONString* this);
void JSONString_free(JSONString* this);
void JSONString_freeString(JSONString* this);
void JSONString_print(JSONString* this, int depth);
int JSONString_parse(JSONString* this, char** chr);

#endif