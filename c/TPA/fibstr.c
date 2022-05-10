// recursivitate - aplicatia 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBINED_LEN 4096

char *make_str_copy(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (!copy) {
        fprintf(stderr, "Malloc error\n");
        exit(EXIT_FAILURE);
    }
    strcpy(copy, s);
    return copy;
}

char *fibo_str_term(size_t n, const char *s0, const char *s1) {
    static char save0[MAX_COMBINED_LEN] = "";
    static char save1[MAX_COMBINED_LEN] = "";
    static char term0[MAX_COMBINED_LEN] = "";
    static char term1[MAX_COMBINED_LEN] = "";

    if (n == 0) {
        return make_str_copy(s0);
    }
    if (n == 1) {
        return make_str_copy(s1);
    }

    strncpy(save0, s0, MAX_COMBINED_LEN);
    strncpy(save1, s1, MAX_COMBINED_LEN);

    strncpy(term0, save1, MAX_COMBINED_LEN);
    strncpy(term1, save0, MAX_COMBINED_LEN);
    strncat(term1, save1, MAX_COMBINED_LEN - strlen(term1));

    return fibo_str_term(n - 1, term0, term1);
}

int main(void) {
    for (size_t i = 0; i < 10; ++i) {
        char *s = fibo_str_term(i, "Hello", "World");
        printf("#%lu: %s\n", i, s);
        free(s);
    }
    return 0;
}