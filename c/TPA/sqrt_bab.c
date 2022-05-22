// recursivitate - aplicatia 2
#include <stdio.h>

// initial call: __my_sqrt(n,n,1,p)
double __my_sqrt(double n, double x, double y, double p) {
    if (x - y <= p)
        return x;
    double new_x = (x + y) / 2;
    return __my_sqrt(n, new_x, n / new_x, p);
}

// wrapper
double my_sqrt(unsigned n, double precision) {
    if (n == 0 || n == 1)
        return n;
    return __my_sqrt(n, n, 1, precision);
}

int main(void) {
    for (unsigned i = 0; i <= 100; ++i)
        printf("sqrt(%u) = %f\n", i, my_sqrt(i, 1e-6));
    return 0;
}