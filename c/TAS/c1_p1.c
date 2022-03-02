#include <stdio.h>
#include <stdint.h>

// bit mask operations
#define GET_FLAG(N,K) ((N >> K) & 1)
#define SET_FLAG(N,K) (N |= (1 << K))
#define UNSET_FLAG(N,K) (N &= ~(1 << K))
#define TOGGLE_FLAG(N,K) (N ^= (1 << K))

// constants
#define MAX_NUM 1000
#define BS 8
#define N (MAX_NUM / BS + 1)

int main(void) {
    uint8_t arr[N] = {0};
    const size_t n = N;

    // read
    uint16_t x = 0;
    while (scanf("%hu", &x) != EOF) {
        SET_FLAG(arr[x / BS], x % BS);
    }
    
    // print
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < BS; ++j) {
            if (GET_FLAG(arr[i], j))
                printf("%lu ", i*BS + j);
        }
    }

    printf("\n");
    return 0;
}