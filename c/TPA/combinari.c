// 3.3 - combinari de n luate cate p

#include <stdio.h>

#define MAX_SIZE 256

static int v[MAX_SIZE] = {0};
static int n = 0;
static int p = 0;

void Init(int k) {
    v[k] = 0;
}

int Successor(int k) {
    if (v[k] < n) {
        v[k]++;
        return 1;
    }
    return 0;
}

int Valid(int k) {
    if (v[k - 1] > v[k])
        return 0;
    for (int i = 1; i < k; ++i)
        if (v[i] == v[k])
            return 0;
    return 1;
}

int Solution(int k) {
    return (k == p);
}

void Print(int k) {
    static int m = 0;
    printf("%d : ", ++m);
    for (int i = 1; i <= k; ++i)
        printf("%d ", v[i]);
    printf("\n");
}

void Back(int n) {
    int k = 1, isS, isV;
    Init(k);
    while (k > 0){
        isS = isV = 0;
        if (k <= n) {
            do {
                isS = Successor(k);
                if (isS) 
                    isV = Valid(k);
            } while (isS && !isV);
        }
        if (isS) {
            if (Solution(k)) {
                Print(k);
            } else {
                k++; 
                Init(k);
            }
        } else {
            k--;
        }
    }
}

int main(void) {
    n = 10;
    p = 3;
    Back(n);
    return 0;
}