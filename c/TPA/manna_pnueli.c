// 2.1

#include <stdio.h>

#define MAX_STACK_SIZE 256

int manna_pnueli(int x) {
    return (x >= 12) ? (x - 1) : manna_pnueli(manna_pnueli(x + 2));
}

int manna_pnueli_stack(int x) {
    static int st[MAX_STACK_SIZE] = { 0 };
    size_t size = 0;
    st[size++] = x;

    while (size) {
        x = st[size - 1];
        if (x < 12) {
            st[size++] = x + 2;
        } else {
            --size;
            st[size - 1] = x - 1;
        }
    }

    return x - 1;
}

int main(void) {
    int x = 6;
    printf("expected: %d\n", manna_pnueli(x));
    printf("actual: %d\n", manna_pnueli_stack(x));
    return 0;
}