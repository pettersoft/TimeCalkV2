//
// Created by pettersoft on 10/25/25.
//

#include "string-functions.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void str_alloc_copy(char **dest, const char *src) {
    if (!*src) return;
    const size_t len = strlen(src);
    *dest = malloc(len + 1);

    if (!*dest) return;

    strcpy(*dest, src);
}

char* clear_whitespace(char* str) {
    if (!str) return NULL;

    const size_t len = strlen(str);
    size_t write = 0;

    for (size_t read = 0; read < len; read++) {
        if (isspace((unsigned char)str[read]) == 0) {
            str[write]=str[read];
            write++;
        }
    }

    str[write] = '\0';

    return str;
}