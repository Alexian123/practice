#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int arr[] = {-1, -2, 0, 2, 4, 6, 8, 9, 10};
    unsigned n = sizeof(arr) / sizeof(int); 

    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0 && arr[i] % 2 != 0) {
            flag = false;
            break;
        }
    }

    if (flag)
        printf("DA!");
    else
        printf("NU!");

    printf("\n");
    return 0;
}