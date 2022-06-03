#include <stdio.h>

#define IN_FILE "sandokan.in"
#define OUT_FILE "sandokan.out"

#define MAX_LEN 2<<13
#define MAX_NUM 2000003

int main(void) {
    FILE *in = fopen(IN_FILE, "r");
    FILE *out = fopen(OUT_FILE, "w");

    int n = 0, k = 0;
    fscanf(in, "%d %d", &n, &k);

    static int a[MAX_LEN] = { 0 };
    a[0] = 1;
    for (int i = 1; i < n; ++i)
        for (int j = i; j >= 1; --j)
            a[j] = (a[j - 1] + a[j]) % MAX_NUM;
    
    fprintf(out, "%d", a[(n - 1) % (k - 1)]);

    return 0;
}