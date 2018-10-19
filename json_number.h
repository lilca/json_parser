#ifndef JSONNUMBER_H
#define JSONNUMBER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <common/typedefs.h>

#include "json_common.h"

struct _JSONNumber {
    double fval;
    long ival;
    char sign;
    long long u_value;
    long long l_value;
    int l_oder;
    char exp_sign;
    long long exp_value;
    int float_flag;
};
typedef struct _JSONNumber JSONNumber;

JSONNumber* JSONNumber_new(void);
void JSONNumber_init(JSONNumber* this);
void JSONNumber_free(JSONNumber* this);
int JSONNumber_isFloat(JSONNumber* this);
void JSONNumber_print(JSONNumber* this, int depth);
int JSONNumber_parse(JSONNumber* this, char** chr);

#endif