#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char** argv) {
    char* p = malloc(20);
    char* idx = p;
    *idx++ = 'a';
    *idx = 'b';

    char* tmp = realloc(p, 100);

    printf("p size = %ld", malloc_usable_size(p));
    printf("p = %lx, tmp = %lx, idx = %lx.\n", (unsigned long)p, (unsigned long)tmp, (unsigned long)idx);
    printf("p = %c, tmp = %c, idx = %c.\n", *p, *tmp, *idx);

    free(tmp);
    return 0;
}

int getSize(void* p) {
    if (p == NULL)
        return 0;
    
    return;
}