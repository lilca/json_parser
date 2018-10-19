#include "json_number.h"

static int _parse_sign (JSONNumber* this, char** chr);
static int _parse_value(JSONNumber* this, char** chr);
static int _parse_l_value(JSONNumber* this, char** chr);
static int _parse_exp_sign(JSONNumber* this, char** chr);
static int _parse_exp_value(JSONNumber* this, char** chr);
static void _format_value(JSONNumber* this);

JSONNumber* JSONNumber_new(void) {
    JSONNumber* res = malloc(sizeof(JSONNumber));
    JSONNumber_init(res);
    return res;
}

void JSONNumber_init(JSONNumber* this) {
    this->fval = 0.0;
    this->ival = 0;
    this->sign = 1;
    this->u_value = 0;
    this->l_value = 0;
    this->l_oder = 0;
    this->exp_sign = 1;
    this->exp_value = 0;
    this->float_flag = FALSE;
    return;
}

void JSONNumber_free(JSONNumber* this) {
    if (this != NULL)
        free(this);
    return;
}

int JSONNumber_isFloat(JSONNumber* this) {
    return this->float_flag;
}

void JSONNumber_print(JSONNumber* this, int depth) {
    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    if (JSONNumber_isFloat(this))
        printf("%le\n", this->fval);
    else
        printf("%ld\n", this->ival);
    return;
}

int JSONNumber_parse(JSONNumber* this, char** chr) {
    // Skip
    JSONCommon_skipChar(chr);

    if (!_parse_sign(this, chr))
        return FALSE;
    if (!_parse_value(this, chr))
        return FALSE;
    if (!_parse_exp_sign(this, chr))
        return FALSE;
    _format_value(this);
    return TRUE;
}

static int _parse_sign (JSONNumber* this, char** chr) {
    if (**chr == '-') {
        this->sign = -1;
        (*chr)++;
    }
    return TRUE;
}

static int _parse_value(JSONNumber* this, char** chr) {
    int res;
    if (**chr == '0') {
        (*chr)++;
        res = _parse_l_value(this, chr);
    } else if (**chr >= '1' && **chr <= '9') {
        this->u_value = **chr - '0';
        (*chr)++;
        while (**chr >= '0' && **chr <= '9') {
            this->u_value = this->u_value * 10 + (**chr - '0');
            (*chr)++;
        }
        res = _parse_l_value(this, chr);
    } else {
        return FALSE;
    }
    if (res != TRUE)
        return FALSE;
    return TRUE;
}

static int _parse_l_value(JSONNumber* this, char** chr) {
    if (**chr == '.'){
        this->float_flag = TRUE;
        (*chr)++;
        while (**chr >= '0' && **chr <= '9') {
            this->l_value = this->l_value * 10 + (**chr - '0');
            this->l_oder++;
            (*chr)++;
        }
    }
    return TRUE;
}

static int _parse_exp_sign(JSONNumber* this, char** chr) {
    int res;
    if (**chr == 'e' || **chr == 'E') {
        this->float_flag = TRUE;
        (*chr)++;
        if (**chr == '+'){
            (*chr)++;
            this->exp_sign = 1;
        } else if (**chr == '-') {
            (*chr)++;
            this->exp_sign = -1;
        }
        res = _parse_exp_value(this, chr);
    }
    return TRUE;
}

static int _parse_exp_value(JSONNumber* this, char** chr) {
    while (**chr >= '0' && **chr <= '9') {
        this->exp_value = this->exp_value * 10 + (**chr - '0');
        (*chr)++;
    }
    return TRUE;
}

static void _format_value(JSONNumber* this) {
    if (this->float_flag) {
        double real;
        if (this->l_value == 0)
            real = (double)this->u_value;
        else
            real = (double)this->u_value +
            ((double)this->l_value / pow(10, this->l_oder));
        real *= (double)this->sign;
        real *= pow(10, (double)this->exp_sign * (double)this->exp_value);
        this->fval = real;
    }
    else {
        this->ival = this->sign * this->u_value;
    }
    return;
}