#include <stdio.h>
#include <stdint.h>

#define IN_FILE "inversmodular.in"
#define OUT_FILE "inversmodular.out"

typedef int64_t i64;

i64 phi(i64 n) {
    i64 x = n;
    for (i64 i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            x = (x / i) * (i - 1);
        }
    }
    if (n != 1)
        x = x / n * (n - 1);
    return x;
}

int main(void) {
    FILE *in = fopen(IN_FILE, "r");
    FILE *out = fopen(OUT_FILE, "w");

    i64 a = 0, n = 0;
    fscanf(in, "%ld %ld", &a, &n);

    i64 expn = phi(n) - 1;
    i64 result = 1;
    for (i64 i = 1; i <= expn; i <<= 1) {
        if (i & expn)
            result = (result * a) % n;
        a = (a * a) % n;
    }

    fprintf(out, "%ld", result);
    return 0;
}