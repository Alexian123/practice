#include <stdio.h>
#include <stdlib.h>

#define IN_FILE "ssm.in"
#define OUT_FILE "ssm.out"

int main(void) {
    FILE *in = fopen(IN_FILE, "r");
    FILE *out = fopen(OUT_FILE, "w");
    if (!in || !out)
        exit(EXIT_FAILURE);

    int n = 0;
    fscanf(in, "%d", &n);

    int *dp = malloc((n + 1) * sizeof(int));
    dp[0] = 0;
    int x = 0, max_s = 0, beg = 0, end = 0, save_i = 0;
    for (int i = 1; i <= n; ++i) {
        fscanf(in, "%d", &x);
        if (x > x + dp[i - 1]) {
            dp[i] = x;
            save_i = i;
        } else {
            dp[i] = x + dp[i - 1];
        }
        if (dp[i] > max_s) {
            max_s = dp[i];
            beg = save_i;
            end = i;
        }
    }
    fclose(in);

    fprintf(out, "%d %d %d", max_s, beg, end);
    fclose(out);
    free(dp);
    return 0;
}