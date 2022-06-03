#include <stdio.h>
#include <stdlib.h>

#define IN_FILE "scmax.in"
#define OUT_FILE "scmax.out"
#define MAX(A,B) (A > B ? A : B)

int main(void) {
    FILE *in = fopen(IN_FILE, "r");
    FILE *out = fopen(OUT_FILE, "w");
    if (!in || !out)
        exit(EXIT_FAILURE);

    int n = 0;
    fscanf(in, "%d", &n);

    size_t *dp = malloc((n + 1) * sizeof(size_t));
    size_t *a = malloc((n + 1) * sizeof(size_t));
    size_t max_dpj = 0, max_len = 0;
    for (int i = 1; i <= n; ++i) {
        fscanf(in, "%ld", &a[i]);
        max_dpj = 0;
        for (int j = 1; j < i; ++j) 
            if (a[j] < a[i])
                max_dpj = MAX(max_dpj, dp[j] + 1);
        dp[i] = MAX(1, max_dpj);
        max_len = MAX(max_len, dp[i]);
    }
    fclose(in);

    fprintf(out, "%ld", max_len);
    fclose(out);
    free(dp);
    return 0;
}