#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

bool is_prime(size_t n) {
    for (size_t i = 2; i*i <= n; ++i)
        if (n % i == 0)
            return false;
    return n >= 2;
}

int get_max_int(int *arr, size_t n) {
    int max = arr[0];
    for (size_t i = 1; i < n; ++i)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

char *sumOfDivided(int *arr, size_t n) {
    static const size_t MAX_TOTAL_LEN = 2048;
    static const size_t MAX_ELEM_LEN = 64;
    char *str = malloc(MAX_TOTAL_LEN);
    memset(str, 0, MAX_TOTAL_LEN);
    char *elem = malloc(MAX_ELEM_LEN);
    memset(elem, 0, MAX_ELEM_LEN);

    // handle 2 separately
    bool found = false;
    int sum = 0;
    for (size_t i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) {
            found = true;
            sum += arr[i];
        }
    }
    if (found) {
        sprintf(elem, "(%d %d)", 2, sum);
        strcat(str, elem);
    }

    int max = get_max_int(arr, n);
    for (size_t i = 3; i <= max; i += 2) {
        if (is_prime(i)) {
            found = false;
            sum = 0;
            for (size_t j = 0; j < n; ++j) {
                if (arr[j] % i == 0) {
                    found = true;
                    sum += arr[j];
                }
            }
            if (found) {
                sprintf(elem, "(%lu %d)", i, sum);
                strcat(str, elem);
            }
        }
    }

    free(elem);
    return str;
}

int main(void) {
    int arr[] = {107, 158, 204, 100, 118, 123, 126, 110, 116, 100};
    size_t n = 10;
    char *str = sumOfDivided(arr, n);
    printf("%s", str);
    printf("\n");
    return 0;
}