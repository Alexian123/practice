#include <stdio.h>
#include <stdlib.h>
#include "object.h"

// bit mask operations
#define GET_FLAG(N,K) ((N >> K) & 1)
#define SET_FLAG(N,K) (N |= (1 << K))
#define UNSET_FLAG(N,K) (N &= ~(1 << K))

static int contents = 0x0; // bit mask to represent contents (1 = selected)
static int max_profit = 0;

// provided in main
extern int N, G;
extern struct Object obj[MAX_OBJECTS];

void Solution() {
    int total_w = 0, total_p = 0;
    for (size_t i = 0; i < N; ++i) {
        if (GET_FLAG(contents, i)) {
            total_w += obj[i].weight;
            total_p += obj[i].profit;
        }
    }

    if (total_w <= G && total_p > max_profit)
        max_profit = total_p;
}

void Back(int i) {
    if (i >= N) {
        Solution();
    }
    else {
        UNSET_FLAG(contents, i);
        Back(i + 1);
        SET_FLAG(contents, i);
        Back(i + 1);
    }
}

int backtracking_solution() {
    Back(0);
    return max_profit;
}