// greedy - aplicatia 2

#include <stdio.h>
#include <stdlib.h>

//#define __DEBUG_INFO 1

// bit mask operations
#define GET_FLAG(N,K) ((N >> K) & 1)
#define SET_FLAG(N,K) (N |= (1 << K))
#define UNSET_FLAG(N,K) (N &= ~(1 << K))

#define INPUT_FILE "rucsac.in"
#define OUTPUT_FILE "rucsac.out"

#define MAX_N 5000

static int N = 0, G = 0;
static int contents = 0x0; // bit mask to represent contents (1 = selected)
static int max_profit = 0;
static struct Object
{
    int weight;
    int profit;
} obj[MAX_N];

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

int main(void) {
    FILE *in = fopen(INPUT_FILE, "r");
    if (!in) {
        fprintf(stderr, "Input file error\n");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(OUTPUT_FILE, "w");
    if (!out) {
        fprintf(stderr, "Output file error\n");
        exit(EXIT_FAILURE);
    }

    // input
    fscanf(in, "%d %d\n", &N, &G);
    for (size_t i = 0; i < N; ++i)
        fscanf(in, "%d %d\n", &obj[i].weight, &obj[i].profit);
    fclose(in);

    Back(0);
    
    // output
    fprintf(out, "%d", max_profit);
    fclose(out);

    return 0;
}