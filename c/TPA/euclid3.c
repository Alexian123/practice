#include <stdio.h>
#include <stdint.h>

#define IN_FILE "euclid3.in"
#define OUT_FILE "euclid3.out"

typedef int64_t i64;

i64 gcd(i64 a, i64 b, i64 *x, i64 *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    i64 x0 = 0, y0 = 0, d = 0;
    d = gcd(b, a % b, &x0, &y0);

    *x = y0;
    *y = x0 - (a / b) * y0;

    return d;
}

int main(void) {
    FILE *in = fopen(IN_FILE, "r");
    FILE *out = fopen(OUT_FILE, "w");

    i64 T = 0;
    fscanf(in, "%ld", &T);

    i64 a = 0, b = 0, c = 0;
    i64 d = 0, x = 0, y = 0;
    for (i64 i = 0; i < T; ++i) {
        fscanf(in, "%ld %ld %ld", &a, &b, &c);

        d = gcd(a, b, &x, &y);
        printf("%ld\n", x * (c / d));

        if (c % d)
            fprintf(out, "0 0\n");
        else
            fprintf(out, "%ld %ld\n", x * (c / d), y * (c / d));
    }

    return 0;
}