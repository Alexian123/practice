#include <stdio.h>
#include <stdlib.h>
#include "object.h"

// provided in main
extern int N, G;
extern struct Object obj[MAX_OBJECTS];

// compare objects based on ratio (for qsort)
int objcmp(const void *o1, const void *o2) {
    const struct Object *obj1 = o1, *obj2 = o2;
    if (obj1->ratio == obj2->ratio)
        return 0;
    return (obj1->ratio < obj2->ratio ? 1 : -1);
}

int greedy_solution() {
    // sort array by ratio
    qsort(obj, N, sizeof(obj[0]), objcmp);

    // calculate profit 
    int max_profit = 0, total_weight = 0;
    for (size_t i = 0; i < N; ++i) {
        if (total_weight + obj[i].weight > G)
            break;
        total_weight += obj[i].weight;
        max_profit += obj[i].profit;
    }

    return max_profit;
}