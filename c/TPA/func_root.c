// recursivitate - aplicatia 3
#include <stdio.h>
#include <stdlib.h>

#define SIGN(NUM) ((NUM > 0) - (NUM < 0))

double f(double x) {
    return x*x*x + 2*x*x + 1;
}

double function_root(double (*f)(double), double a, double b, double p) {
    if (a >= b || SIGN(f(a)) == SIGN(f(b))) // [a,b] not a proper interval
        return 0;
    double c = (a + b) / 2;
    if (f(c) == 0 || b - a <= p)
        return c;
    if (SIGN(f(a)) != SIGN(f(c)))
        return function_root(f, a, c, p);
    return function_root(f, c, b, p);
}

int main(void) {
    printf("%f\n", function_root(f, -4, 4, 1e-7));
    return 0;
}