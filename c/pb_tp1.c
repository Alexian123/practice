#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define NUM_FUNCTIONS 4
#define MAX_NAME_LEN 5

void compare_results(double (*funcs[NUM_FUNCTIONS])(double), double x) {
    char match = funcs[0](x) == sin(x) && funcs[1](x) == cos(x) && 
                 funcs[2](x) == log(x) && funcs[3](x) == sqrt(x);
    if (match) {
        printf("Totul este OK!\n");
    } else {
        printf("Nu este OK!\n");
    }
}

int main() {
    double (*funcs[NUM_FUNCTIONS])(double) = {sin, cos, log, sqrt};
    char names[NUM_FUNCTIONS][MAX_NAME_LEN] = {"sin", "cos", "log", "sqrt"};

    double x = 0.0;
    printf("Introdu un nr (double):");
    scanf("%lf", &x);

    char input[MAX_NAME_LEN] = "";
    printf("Alege o functie (sin, cos, log, sqrt):");
    scanf("%4s", input);

    char found_match = 0;
    for (size_t i = 0; i < NUM_FUNCTIONS; ++i) {
        if (strcmp(input, names[i]) == 0) {
            found_match = 1;
            printf("%s(%lf) = %lf\n", names[i], x, funcs[i](x));
            break;
        }
    }

    if (!found_match) {
        printf("Nu exista functia \"%s\"!\n", input);
        //exit(EXIT_FAILURE);
    }

    compare_results(funcs, x);

    printf("\narray\t\toriginal\n");
    printf("%p\t%p\n", &funcs[0], &sin);
    printf("%p\t%p\n", &funcs[1], &cos);
    printf("%p\t%p\n", &funcs[2], &log);
    printf("%p\t%p\n", &funcs[3], &sqrt);

    return 0;
}