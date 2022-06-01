#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define NUM_VAR 4

const char var[NUM_VAR] = { 'c', 'b', 'g', 'a' };
int max_var[] = { 0, // max c
                  0,  // max b
                  0,  // max g
                  0 }; // max a
int count_var[] = { 0, // c
                    0,  // b
                    0,  // g
                    0 }; // a

int st[MAX_SIZE] = { 0 };

void Init(int k) {
    st[k] = -1;
}

int Successor(int k) {
    if (count_var[st[k]] < max_var[st[k]]) {
        ++count_var[st[k]];
        return 1;
    } else if (st[k] < NUM_VAR - 1) {
        ++st[k];
        return 1;
    }
    return 0;
}

int Valid(int k) {
    for (int i = 1; i < k; ++i) {
        switch (var[st[i]]) {
            case 'c':
                return (var[st[i+1]] == 'c' || var[st[i+1]] == 'g') &&
                       (var[st[i-1]] == 'c' || var[st[i-1]] == 'g');
            case 'b':
                return (var[st[i+1]] == 'b' || var[st[i+1]] == 'c') &&
                       (var[st[i-1]] == 'b' || var[st[i-1]] == 'c');
            case 'g':
                return (var[st[i+1]] == 'g') && (var[st[i-1]] == 'g');
            case 'a':
                return (var[st[i+1]] == 'a' || var[st[i+1]] == 'g') &&
                       (var[st[i-1]] == 'a' || var[st[i-1]] == 'g');
        }
    }
    return 1;
}

int Solution(int k, int n) {
    return (k == n - 1);
}

void Print(int n) {
    static int m = 0;
    printf("%d : ", ++m);
    for (int i = 0; i < n; ++i)
        printf("%c ", var[st[i]]);
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
    max_var[0] = 2;
    max_var[1] = 3;
    max_var[2] = 4;
    max_var[3] = 5;
    int n = 0;
    for (int i = 0; i < NUM_VAR; ++i)
        n += max_var[i];
    Back(n);
    return 0;
}