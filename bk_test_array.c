#include <stdio.h>
#include <string.h>

//#include "json_number.h"
//#include "json_string.h"
//#i/nclude "json_value.h"
#include "json_array.h"

char string[4096];

int main(int argc, char** argv) {
    string[0] = '\0';
    while (strcmp(string, "e") != 0) {
        scanf("%s", string);
        char* chr = string;
        //

        JSONArray* array = JSONArray_new();
        if (JSONArray_parse(array, &chr)) {
            JSONArray_print(array, 0);
            printf("%s is array(%ld).\n", string, array->size);
        }
        else
            printf("%s is not array.\n", string);
        printf("----------------------\n");
        JSONArray_free(array);
    }
    return 0;
}