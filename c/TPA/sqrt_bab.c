// recursivitate - aplicatia 2
#include <stdio.h>
#include <stdlib.h>

double __my_sqrt(double x, double init, size_t steps) {
    if (steps == 0 || x == 0)
        return init;
    return __my_sqrt(x, 0.5 * (init + x / init), steps - 1);
}

double my_sqrt(size_t num) {
    return __my_sqrt((double) num, 1, 100);
}

int main(void) {
    for (size_t i = 0; i <= 100; ++i)
        printf("sqrt(%lu) = %f\n", i, my_sqrt(i));
    return 0;
}