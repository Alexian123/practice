// 2.2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

char pr(char op) {
    switch (op) { // operator
        case '(':
        case ')':
            return 0;
        case '*':
        case '/':
            return 1;
        case '+':
        case '-':
            return 2;
    }
    return -1; // operand
}

char *convert_to_postfix(const char *expr) {
    static char st[MAX_SIZE] = { 0 };
    size_t size = 0;

    static char res[MAX_SIZE] = { 0 };
    size_t len = 0;

    for (size_t i = 0; i < MAX_SIZE && expr[i] != 0; ++i) {
        if (pr(expr[i]) == -1) {
            res[len++] = expr[i];
        } else if (expr[i] == '(') {
            st[size++] = expr[i];
        } else if (expr[i] == ')') {
            while (st[size - 1] != '(') {
                res[len++] = st[size - 1];
                --size;
            }
            --size;
        } else {
            while (size && pr(st[size - 1]) == 1) {
                res[len++] = st[size - 1];
                --size;
            }
            st[size++] = expr[i];
        }
    }

    while (size) {
        res[len++] = st[size - 1];
        --size;
    }
    res[len] = 0;

    char *s = malloc(len + 1);
    if (!s)
        return NULL;
    strcpy(s, res);
    return s;
}

float eval_postfix(const char *pf, const float *values, size_t n) {
    static float st[MAX_SIZE] = { 0 };
    size_t size = 0;
    size_t k = 0;
    for (size_t i = 0; i < MAX_SIZE && pf[i] != 0; ++i) {
        if (pr(pf[i]) == -1) {
            st[size++] = values[k++];
        } else {
            float y = st[size - 1];
            --size;
            float x = st[size - 1];
            switch (pf[i]) {
                case '+':
                    st[size - 1] = x + y;
                    break;
                case '-':
                    st[size - 1] = x - y;
                    break;
                case '*':
                    st[size - 1] = x * y;
                    break;
                case '/':
                    st[size - 1] = x / y;
                    break;
            }
        }
    }
    return st[size - 1];
}

int main(void) {
    char expr[MAX_SIZE] = "";
    float values[MAX_SIZE] = { 0 };
    size_t n = 0;

    printf("expr=");
    fgets(expr, MAX_SIZE, stdin);
    expr[strcspn(expr, "\r\n")] = 0;
    for (;;) {
        printf("value[%lu]=", n);
        if (scanf("%f", &values[n]) == EOF)
            break;
        ++n;
    }

    char *pf = convert_to_postfix(expr);
    printf("\npostfix: %s\n", pf);
    printf("result: %f\n", eval_postfix(pf, values, n));

    return 0;
}