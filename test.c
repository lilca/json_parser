#include <stdio.h>
#include <string.h>

#include <iobuffer/iobuffer.h>
//#include "json_number.h"
//#include "json_string.h"
//#i/nclude "json_value.h"
#include "json_object.h"

int main(int argc, char** argv) {
    IOBuffer* buf = IOBuffer_readFile("test.dat");

    JSONObject* obj = JSONObject_new();
    char* chr = buf->data;
    if (JSONObject_parse(obj, &chr)) {
        JSONObject_print(obj, 0);
        printf("%s is object(%ld).\n", "@", obj->size);
    } else
        printf("%s is not object.\n", "@");
    printf("----------------------\n");
    JSONObject_free(obj);
    obj = NULL;

    IOBuffer_free(buf);
    return 0;
}