#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 18

char *range_extraction(const int *args, size_t n) {
    static char token[MAX_TOKEN_LEN] = "";
    char *range = (char*) malloc(MAX_TOKEN_LEN * n + 1);
    if (!range)
        return NULL;
    memset(range, 0, MAX_TOKEN_LEN * n + 1);

    if (n == 1) {
        sprintf(range, "%d", args[0]);
        return range;
    }

    size_t start_index = 0, end_index = 0;
    size_t count = 1;
    while (start_index < n - 1) {
        count = 1;
        for (size_t i = start_index + 1; i < n; end_index = ++i - 1) {
            if (args[i] != args[i - 1] + 1) {
                end_index = i - 1;
                break;
            }
            ++count;
        }
        if (count < 3) {
            for (size_t i = start_index; i <= end_index; ++i) {
                snprintf(token, MAX_TOKEN_LEN, "%d,", args[i]);
                strncat(range, token, MAX_TOKEN_LEN);
            }
        } else {
            snprintf(token, MAX_TOKEN_LEN, "%d-%d,", args[start_index], args[end_index]);
            strncat(range, token, MAX_TOKEN_LEN);
        }
        start_index = (end_index > start_index) ? end_index + 1 : start_index + 1;
    }

    if (end_index == n - 2) {
        // last element (in case it is not in a range)
        snprintf(token, MAX_TOKEN_LEN, "%d", args[end_index + 1]);
        strncat(range, token, MAX_TOKEN_LEN);
    } else {
        // remove last comma
        range[strlen(range) - 1] = '\0';
    }if (n == 1) {
        sprintf(range, "%d", args[0]);
        return range;
    }

    return range;
}

int main(void) {
    char *range = range_extraction((const int[]){ -6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20 }, 20);
    printf("%s", range);
    printf("\n");
    return 0;
}