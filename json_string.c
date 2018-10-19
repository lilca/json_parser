#include "json_string.h"

static int _utf8(uint8** chr, char** buf);

JSONString* JSONString_new(void) {
    JSONString* res = malloc(sizeof(JSONString));
    JSONString_init(res);
    return res;
}

void JSONString_init(JSONString* this) {
    this->buf = NULL;
    this->size = 0;
    return;
}

void JSONString_free(JSONString* this) {
    JSONString_freeString(this);
    if (this != NULL)
        free(this);
    return;
}

void JSONString_freeString(JSONString* this) {
    if (this == NULL)
        return;
    if (this->buf != NULL) {
        free(this->buf);
        this->buf = NULL;
    }
    return;
}

void JSONString_print(JSONString* this, int depth) {
    for (int idx = 0; idx < depth; idx++)
        printf(" ");
    printf("%s\n", this->buf);
    return;
}

int JSONString_parse(JSONString* this, char** chr) {
    char buf[JSON_STRING_BLOCK];
    char* p = buf;

    // Skip
    JSONCommon_skipChar(chr);

    if (**chr != '\"')
        return FALSE;
    (*chr)++;
    while (**chr != '\"') {
        if (**chr == '\\') {
            (*chr)++;
            switch (**chr) {
                case '\"' :
                case '\\' :
                case '/' : *p++ = **chr; (*chr)++; break;
                case 'b' : *p++ = '\x08'; (*chr)++; break;
                case 'f' : *p++ = '\x0c'; (*chr)++; break;
                case 'n' : *p++ = '\x0a'; (*chr)++; break;
                case 'r' : *p++ = '\x0d'; (*chr)++; break;
                case 't' : *p++ = '\x09'; (*chr)++; break;
                case 'u' :
                    if (!_utf8((uint8**)chr, &p))
                        return FALSE;
                    break;
                default : return FALSE;
            }
        } else if (**chr == '\0') {
             return FALSE;
        }else {
            *p++ = **chr;
            (*chr)++;
        }
    }
    (*chr)++;
    *p = '\0';
    //
    this->buf = realloc(this->buf, strlen(buf) + 1);
    if (this->buf == NULL) {
        JSONString_freeString(this);
        return FALSE;
    }
    strcpy((char*)this->buf, buf);
    this->size = strlen((char*)(this->buf));
    return TRUE;
}

static int _utf8(uint8** chr, char** buf) {
    (*chr)++;
    uint16 tmp = 0;
    for (int idx = 0; idx < 4; idx++) {
        if (**chr >= '0' && **chr <= '9') {
            tmp = tmp * 16 + **chr - '0';
            (*chr)++;
        } else if (**chr >= 'a' && **chr <= 'f') {
            tmp = tmp * 16 + **chr - 'a' + 10;
            (*chr)++;
        } else if (**chr >= 'A' && **chr <= 'F') {
            tmp = tmp * 16 + **chr - 'A' + 10;
            (*chr)++;
        } else
            return FALSE;
    }
    if (tmp < 0x0100) {
        **buf = (uint8)tmp;
        (*buf)++;
    } else {
        **buf = (uint8)(tmp / 256);
        (*buf)++;
        **buf = (uint8)tmp;
        (*buf)++;
    }
    return TRUE;
}
