#include "json_common.h"

void JSONCommon_skipChar(char** chr) {
    while (**chr == ' ' || **chr == '\t' || **chr == '\n' || **chr == '\r') {
        (*chr)++;
    }
    return;
}
