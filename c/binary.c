#include <stdio.h>
#include <stdlib.h>

void print_binary(unsigned n) {
    static const size_t N_BITS = sizeof(n) * 8;
    for (int i = N_BITS - 1; i >= 0; --i) {
        if (n & (1 << i))
            printf("1");
        else
            printf("0");
        if (i % 4 == 0)
            printf(" ");
    }
    printf("\n");
}

int main(void) {
    print_binary(13);
    return 0;
}