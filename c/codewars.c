#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

char *capitalize(char *s) {
    if (!s)
        return NULL;
    size_t n = strlen(s);
    for (size_t i = 0; i < n; ++i)
        s[i] = toupper(s[i]);
    return s;
}

char *DuplicateEncoder(const char *s) {
    if (!s)
        return NULL;
    size_t n = strlen(s);

    char *res = (char*) malloc(n + 1);
    if (!res)
        return NULL;

    char *s_copy = (char*) malloc(n + 1);
    if (!s_copy)
        return NULL;

    strncpy(res, s, n);
    capitalize(res);
    strncpy(s_copy, res, n);

    for (size_t i = 0; i < n; ++i) {
        char *p = strchr(s_copy, res[i]);
        char *q = strrchr(s_copy, res[i]);
        if (p && q && p != q)
            res[i] = ')';
        else
            res[i] = '(';
    }
  
    return res;
}

int main(void) {

    char *s = DuplicateEncoder("P");
    printf("%s", s);

    printf("\n");
    return 0;
}