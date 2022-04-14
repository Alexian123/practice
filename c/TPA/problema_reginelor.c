// 3.4

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define ROWS 8
#define COLS 8

struct P
{
    int i;
    int j;
};

static struct P st[MAX_SIZE];

void Init(int k) {
    st[k].i = -1;
    st[k].j = -1;
}

int Successor(int k) {
    if (st[k].j < COLS - 1) {
        ++(st[k].j);
        if (st[k].i == -1)
            st[k].i = 0;
        return 1;
    } else if (st[k].i < ROWS - 1) {
        ++(st[k].i);
        st[k].j = 0;
        return 1;
    }
    return 0;
}

int Valid(int k) {
    for (int z = 0; z < k; ++z)
        if (st[z].i == st[k].i || st[z].j == st[k].j ||
            abs(st[z].i - st[k].i) == abs(st[z].j - st[k].j))
            return 0;
    return 1;
}

int Solution(int k, int n) {
    return (k == n - 1);
}

void Print(int n) {
    static int m = 0;
    printf("%d : ", ++m);
    for (int z = 0; z < n; ++z)
        printf("(%d, %d) ", st[z].i, st[z].j);
    printf("\n");
}

void Back(int n) {
    int k = 0, isS, isV;
    Init(k);
    while (k > -1) {
        isS = isV = 0;
        if (k < n) {
            do {
                isS = Successor(k);
                if (isS)
                    isV = Valid(k);
            } while (isS && !isV);
        }
        if (isS) {
            if (Solution(k, n)) {
                Print(n);
            } else {
                ++k;
                Init(k);
            }
        } else {
            --k;
        }
    }
}

int main(void) {
    Back(8);
    return 0;
}