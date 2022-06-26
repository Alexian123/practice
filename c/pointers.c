#include <stdio.h>

void func(int **x) {
    int n = 200;
    *x = &n;
}

int main() {
    int n = 100;
    int *x = &n;
    printf("%d\n", *x);
    func(&x);
    printf("%d\n", *x);
    return 0;
}