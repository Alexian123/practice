#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_FILE "alpin.in"
#define OUT_FILE "alpin.out"
#define MAX(A,B) ((A) > (B) ? (A) : (B))

char is_valid(int i, int j, int n) {
    return i >= 0 && i < n && j >= 0 && j < n;
}

int dynamic(int i, int j, int n, int **dp, int **a) {
    static const int dx[] = {1, -1, 0, 0};
    static const int dy[] = {0, 0, 1, -1};
    static const int dn = sizeof(dx) / sizeof(dx[0]);

    if (dp[i][j] > 0)
        return dp[i][j];

    int len = 0, x = 0, y = 0;
    for (int k = 0; k < dn; ++k) {
        x = i + dx[k];
        y = j + dy[k];
        if (is_valid(x, y, n) && a[x][y] > a[i][j]) {
            int new_len = 1 + dynamic(x, y, n, dp, a);
            len = MAX(len, new_len);
        }
    }
    return dp[i][j] = len;
}

int get_max_len(int **a, int n) {
    int **dp = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        dp[i] = malloc(n * sizeof(int));
        memset(dp[i], 0, n * sizeof(int));
    }

    int max_len = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            max_len = MAX(max_len, 1 + dynamic(i, j, n, dp, a));

    for (int i = 0; i < n; ++i)
        free(dp[i]);
    free(dp);
    return max_len;
}

int main(void) {
    FILE *in = fopen(IN_FILE, "r");
    FILE *out = fopen(OUT_FILE, "w");
    if (!in || !out)
        exit(EXIT_FAILURE);

    int n = 0;
    fscanf(in, "%d", &n);

    int **a = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        a[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j)
            fscanf(in, "%d", &a[i][j]);
    }
    fclose(in);

    fprintf(out, "%d", get_max_len(a, n));
    fclose(out);
    return 0;
}