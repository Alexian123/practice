// greedy - aplicatia 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "object.h"

#define MILIS_PER_SECOND 1000

#define NUM_INPUT_FILES 11
#define MAX_FILE_NAME_LEN 32

static char file_names[NUM_INPUT_FILES][MAX_FILE_NAME_LEN] = {
    "input/5.in", "input/6.in", "input/7.in", "input/8.in", "input/9.in", "input/10.in",
    "input/11.in", "input/12.in", "input/13.in", "input/14.in", "input/15.in"
};

int N = 0, G = 0;
struct Object obj[MAX_OBJECTS];

extern int greedy_solution();
extern int backtracking_solution();

int main(void) {
    FILE *in = NULL;
    for (size_t i = 0; i < NUM_INPUT_FILES; ++i) { // go through all files
        in = fopen(file_names[i], "r");
        if (!in) {
            fprintf(stderr, "Input file error: \"%s\"\n", file_names[i]);
            continue;
        }

        // read input from file
        fscanf(in, "%d %d\n", &N, &G);
        for (size_t i = 0; i < N; ++i) {
            fscanf(in, "%d %d\n", &obj[i].weight, &obj[i].profit);
            obj[i].ratio = (float) obj[i].profit / (float) obj[i].weight;
        }
        fclose(in);

        clock_t t0, t1, t2; // timers

        // solve using greedy and backtracking
        t0 = clock();
        int greedy = greedy_solution();
        t1 = clock();
        int back = backtracking_solution();
        t2 = clock();

        // print data
        printf("N: %ld\nGreedy solution: %d -> time: %lfms\nBacktracking solution: %d -> time: %lfms\n", 
                i + 5, greedy, ((double) (t1 - t0) / CLOCKS_PER_SEC) * MILIS_PER_SECOND, back, ((double) (t2 - t1) / CLOCKS_PER_SEC) * MILIS_PER_SECOND);
        printf("---------------------------------------------------------------\n\n");

    }
}