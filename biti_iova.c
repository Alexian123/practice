#include <stdio.h>
#include <stdint.h>

// 1001 1011 0110 0010 0000 1110 0011 1110
// 1110 0011 1110 0000 0010 0110 1011 1001

void print_nibbles(uint32_t n) {
    for (int i = 31; i >= 0; --i) {
        if (n & (1 << i))
            printf("1");
        else
            printf("0");
        if (i % 4 == 0)
            printf(" ");
    }
}

// 0000 0000 0000 0000 0000 0000 0000 0000
uint32_t swap_nibbles(uint32_t n) {
    uint32_t m = 0;

    for (int i = 31; i >= 0; i -= 4) {
        for (int j = 0; j < 4; ++j) {
            if (n & (1 << (31 - i + 3 - j)))
                m |= (1 << (i - j));
        }
    }

    return m;
}

int main(void) {
    uint32_t n = 0b10011011011000100000111000111110;
    print_nibbles(n);
    printf("\n");
    print_nibbles(swap_nibbles(n));
    printf("\n");
    return 0;
}