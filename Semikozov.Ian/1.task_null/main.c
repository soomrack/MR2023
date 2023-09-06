#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    char *ptrStr = (char*)malloc(sizeof(char) * 14);
    strcpy(ptrStr, "Hello, world!");
    printf("%s\n", ptrStr);
    free(ptrStr);
    return 0;
}