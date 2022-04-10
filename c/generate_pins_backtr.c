#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_PIN "X" // marks end of pins array (for cleanup function)

// initialize the "stack"
void init_stack(int *st, int k) {
    st[k] = -1;
}

// check for a possible successor
int is_successor(int *st, int k) {
    if (st[k] < 9) {
        ++st[k];
        return 1;
    }
    return 0;
}

// check if digit a is adjacent or equal to digit b
int is_valid_digit(int a, int b) {
    if (a == b)
        return 1;
    switch (b) {
        case 0:
            return a == 8;
        case 1:
            return (a == 2) || (a == 4);
        case 2:
            return (a == 1) || (a == 5) || (a == 3);
        case 3:
            return (a == 2) || (a == 6);
        case 4:
            return (a == 1) || (a == 5) || (a == 7);
        case 5:
            return (a == 2) || (a == 4) || (a == 8) || (a == 6);
        case 6:
            return (a == 3) || (a == 5) || (a == 9);
        case 7:
            return (a == 4) || (a == 8);
        case 8:
            return (a == 5) || (a == 7) || (a == 0) || (a == 9);
        case 9:
            return (a == 6) || (a == 8);
    }
    return 0;
}

// check if the pin being generated contains valid digirs so far
int is_valid(int *st, int k, const int *digits) {
    // check if the digits are adjacent or equal to the ones in the observed pin
    for (int i = 0; i <= k; ++i)
        if (!is_valid_digit(st[i], digits[i]))
            return 0;
    return 1;
}

// check if generated pin is a solution
int is_solution(int k, int len) {
    return (k == len - 1);
}

// add valid pin to list
void add_solution(int *st, int len, char **pins, size_t *count) {
    for (int i = 0; i < len; ++i)
        pins[*count][i] = st[i] + '0';
    pins[*count][len] = 0;
    ++(*count);
}

// backtracking main function
void back(const int *digits, int len, char **pins, size_t *count) {
    static int st[9] = {0};
    int k = 0, isS, isV;
    init_stack(st, k);
    while (k > -1){
        isS = isV = 0;
        if (k < len) {
            do {
                isS = is_successor(st, k);
                if (isS) 
                    isV = is_valid(st, k, digits);
            } while (isS && !isV);
        }
        if (isS) {
            if (is_solution(k, len)) {
                add_solution(st, len, pins, count);
            } else {
                ++k; 
                init_stack(st, k);
            }
        } else {
            --k;
        }
    }
}

int pow_int(int base, int exp) {
    int p = 1;
    for (int i = 0; i < exp; ++i)
        p *= base;
    return p;
}

// will assume malloc won't ever fail for simplicity
char **get_pins(const char *observed, size_t *count) {
    *count = 0;
    int len = strlen(observed);
    // allocate for max num of possible pins (5 to the power of len)
    int max_pins = pow_int(5, len);
    char **pins = malloc(sizeof(char*) * (max_pins + 1)); // +1 for END_PIN
    for (int i = 0; i < max_pins + 1; ++i) {
        pins[i] = malloc(len + 1);
        memset(pins[i], 0, len + 1);
    }
    strcpy(pins[max_pins], END_PIN); // set END_PIN

    // copy the observed pin's digits into an array
    static int digits[9] = {0};
    for (size_t i = 0; i < len; ++i)
        digits[i] = observed[i] - '0';

    // generate pins using backtracking method
    // will also generate the observed pin
    back(digits, len, pins, count);

    return pins;
}

void free_pins(char **pins) {
    if (!pins)
        return;
    size_t i = 0;
    while (strcmp(pins[i], END_PIN) != 0)
        free(pins[i++]);
    free(pins[i]);
    free(pins);
}

int main(void) {
    size_t count = 0;
    char **pins = get_pins("369", &count); 
    printf("%lu\n", count);
    for (size_t i = 0; i < count; ++i)
        printf("%s ", pins[i]);
    free_pins(pins);
    printf("\n");
    return 0;
}