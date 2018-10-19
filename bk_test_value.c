#include <stdio.h>
#include <string.h>

#include "json_number.h"
#include "json_string.h"
#include "json_value.h"

char string[4096];

int main(int argc, char** argv) {
    string[0] = '\0';
    while (strcmp(string, "e") != 0) {
        scanf("%s", string);
        char* chr = string;
        //

        JSONValue* data = JSONValue_new();
printf("%s", string);
        if (JSONValue_parse(data, &chr)) {
            switch (data->type) {
                case JSON_TYPE_STRING : {
                    JSONString* tmp = (JSONString*)data->val;
                    printf("[%s] is string.(%s)\n", string, tmp->buf); break;}
                case JSON_TYPE_NUMBER : {
                    JSONNumber* tmp = (JSONNumber*)data->val;
                    if (JSONNumber_isFloat(tmp))
                        printf("[%s] is float.(%e)\n", string, tmp->fval);
                    else
                        printf("[%s] is integer.(%ld)\n", string, tmp->ival);
                    break;}
                case JSON_TYPE_OBJECT : printf("[%s] is object.\n", string); break;
                case JSON_TYPE_ARRAY : printf("[%s] is array.\n", string); break;
                case JSON_TYPE_TRUE : printf("[%s] is true.\n", string); break;
                case JSON_TYPE_FALSE : printf("[%s] is false.\n", string); break;
                case JSON_TYPE_NULL : printf("[%s] is null.\n", string); break;
                default : printf("[%s] is unknow token.\n", string); break;
            }
        }
        else
            printf("[%s] is unknow token.\n", string);

        JSONValue_free(data);
    }
    return 0;
}