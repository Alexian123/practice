#include <stdio.h>
#include "stack_arr.h"

int manna_pnueli(int x) {
    return (x >= 12) ? (x - 1) : manna_pnueli(manna_pnueli(x + 2));
}

int manna_pnueli_stack(int x) {
    Stack *s = createStack(16);
    push(s, x);
    int y;

    for (;;) {
        y = pop(s);
        if (getStackSize(s) == 0 && y >= 12) {
            break;
        }

        if (y < 12) {
            push(s, y);
            push(s, y + 2);
        } else {
            pop(s);
            push(s, y - 1);
        }
    }

    destroyStack(s);
    return y - 1;
}

int main(void) {
    int x = 6;
    printf("expected: %d\n", manna_pnueli(x));
    printf("actual: %d\n", manna_pnueli_stack(x));
    return 0;
}