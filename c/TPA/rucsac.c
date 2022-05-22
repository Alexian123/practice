// greedy - aplicatia 1

#include <stdio.h>
#include <stdlib.h>

//#define __DEBUG_INFO 1

#define INPUT_FILE "rucsac.in"
#define OUTPUT_FILE "rucsac.out"

#define MAX_N 5000

static int N = 0, G = 0;
static struct Object
{
    int weight;
    int profit;
    float ratio; // profit / weight unit
} obj[MAX_N];

// compare objects based on ratio (for qsort)
int objcmp(const void *o1, const void *o2) {
    const struct Object *obj1 = o1, *obj2 = o2;
    if (obj1->ratio == obj2->ratio)
        return 0;
    return (obj1->ratio < obj2->ratio ? 1 : -1);
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
    for (size_t i = 0; i < N; ++i) {
        fscanf(in, "%d %d\n", &obj[i].weight, &obj[i].profit);
        obj[i].ratio = (float) obj[i].profit / (float) obj[i].weight;
    }
    fclose(in);

    // sort array by ratio
    qsort(obj, N, sizeof(obj[0]), objcmp);

#ifdef __DEBUG_INFO
    for (size_t i = 0; i < N; ++i)
        printf("#%ld - %d - %d - %f\n", i, obj[i].profit, obj[i].weight, obj[i].ratio);
#endif

    // calculate profit 
    int max_profit = 0, total_weight = 0;
    for (size_t i = 0; i < N; ++i) {
        if (total_weight + obj[i].weight > G)
            break;
        total_weight += obj[i].weight;
        max_profit += obj[i].profit;
    }

    // output
    fprintf(out, "%d", max_profit);
    fclose(out);

    return 0;
}