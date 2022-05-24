#include "string_extra.h"
#include <string.h>
#include <ctype.h>

char *strrpl(char *dest, const char *s1, const char *s2)
{
    if (!dest || !s1 || !s2)
        return dest;

    char *temp = (char*) malloc((strlen(dest) + 1) * sizeof(char));
    if (!temp)
        return dest;

    char *p = NULL;
    while ((p = strstr(dest, s1))) {
        strcpy(temp, "");
        strncat(temp, dest, p - dest);
        strcat(temp, s2);
        strcat(temp, p + strlen(s1));
        strcpy(dest, temp);
    }

    free(temp);
    return dest;
}

char *strnrpl(char *dest, const char *s1, const char *s2, size_t n)
{
    if (!dest || !s1 || !s2 || !n)
        return dest;

    char *temp = (char*) malloc((n+1) * sizeof(char));
    if (!temp)
        return dest;

    char *p = NULL;
    while ((p = strstr(dest, s1))) {
        strncpy(temp, "", n);
        strncat(temp, dest, p - dest);
        strncat(temp, s2, n - strlen(temp) - 1);
        strncat(temp, p + strlen(s1), n - strlen(temp) - 1);
        strncpy(dest, temp, n);
    }

    free(temp);
    return dest;
}

char *strrpl_d(const char *dest, const char *s1, const char *s2)
{
    if (!dest || !s1 || !s2)
        return NULL;

    // calculate exact size for new string
    size_t n = strlen(dest) + 1; // +1 for '\0'
    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);
    size_t count = 0;
    char *p = strstr(dest, s1);
    while (p) {// count occurences of s1 in dest
        ++count;
        p = strstr(p + strlen(s1), s1);
    }
    char *temp = NULL; // temp will always have the maximum size
    if (s2_len > s1_len) {
        n += count * (s2_len - s1_len);
        temp = (char*) malloc(n * sizeof(char)); // size of result is greater
    }
    else {
        temp = (char*) malloc(n * sizeof(char)); // size of dest is greater
        n -= count * (s1_len - s2_len);
    }

    if (!temp)
        return NULL;
    strcpy(temp, dest);

    // new_str will now have the exact size required
    char *new_str = (char*) malloc(n * sizeof(char));
    if (!new_str)
        return NULL;
    
    // it is now safe to use strrpl on temp
    strrpl(temp, s1, s2);

    // copy the result to the exact size string
    strcpy(new_str, temp);

    free(temp);
    return new_str;
}