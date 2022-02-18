#include <stdio.h>

#define MAX_LEN 256

int main(void) {
    int arr[MAX_LEN] = {0};
    int arr2[MAX_LEN] = {0};
    unsigned n = 0, k = 0;

    while (scanf("%d", &arr[n]) != EOF) {
        ++n;
        if (n >= MAX_LEN)
            break;
    }
    
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] < arr[i+1])
            continue;
        arr2[k++] = arr[i];
    }
    arr2[k++] = arr[n - 1];

    for (int i = 0; i < k; ++i)
        printf("%d ", arr2[i]);

    printf("\n");
    return 0;
}