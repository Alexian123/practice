/*  PREFIX NOTATION EVALUATION
   - the terms must be letters from the English alphabet (uppercase or lowercase);
   - you must provide an array of values (doubles) for the expression terms;
   - the length of the array will not be verified;
   - the index parameter represents a pointer to the index of the first element of the array.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// checks if c is one of the possible operators
int is_operator(int c) {
    return (c == '+') || (c == '-') ||
           (c == '*') || (c == '/');
}

// general function for evaluating prefix expression (use the appropriate wrapper)
double eval_prefix(FILE *stream, const double *values, size_t *index) {
    int c = fgetc(stream);
    if (is_operator(c)) {
        double x = eval_prefix(stream, values, index);
        double y = eval_prefix(stream, values, index);
        switch (c) {
            case '+':
                return x + y;
            case '-':
                return x - y;
            case '*':
                return x * y;
            case '/':
                return x / y;
        }
    }
    return values[(*index)++]; // increment the index
}

// for streams, portable
double eval_prefix_stream(FILE *stream, const double *values) {
    size_t index = 0;
    return eval_prefix(stream, values, &index);
}

// for strings, not portable
double eval_prefix_string(const char *expr, const double *values) {
    char *e = strdup(expr);
    if (!e)
        return 0;
    FILE *stream = fmemopen(e, strlen(e), "r");
    if (!stream)
        return 0;
    size_t index = 0;
    double result = eval_prefix(stream, values, &index);
    fclose(stream);
    free(e);
    return result;
}

int main(void) {
    const char *expr = "-/*+aAbBc";
    const double values[] = {2, 3, 4, 3, 6};
    printf("%f\n", eval_prefix_string(expr, values));
    const char *expr2 = "+-*/efgHi";
    const double values2[] = {5, 2, 30, 5.5, -0.5};
    printf("%f\n", eval_prefix_string(expr2, values2));
    return 0;
}