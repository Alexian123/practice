#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_PINS 27

size_t power(size_t a, size_t b) {
    size_t p = 1;
    for (size_t i = 0; i < b; ++i)
        p *= a;
    return p;
}

void add_pin_with_changed_digit(char **pins, size_t *count, const char *observed, size_t index, int digit) {
    strcpy(pins[*count], observed);
    pins[*count][index] = digit + '0'; 
    ++(*count);
}

char **get_pins(const char *observed, size_t *count) {
    if (!count)
        return NULL;
    if (!observed) {
        *count = 0;
        return NULL;
    }
    *count = 1;

    const size_t pin_length = strlen(observed);
    char **pins = malloc(MAX_PINS * sizeof(char*));
    if (!pins) {
        *count = 0;
        return NULL;
    }
    for (size_t i = 0; i < MAX_PINS; ++i) {
        pins[i] = malloc(pin_length + 1);
        if (!pins[i]) { // cleanup
            *count = 0;
            for (size_t j = 0; j < i; ++j)
                free(pins[j]);
            free(pins);
            return NULL;
        }
    }
    strcpy(pins[0], observed);

    for (size_t i = 0; i < pin_length; ++i) {
        int digit = observed[i] - '0';
        switch (digit) {
            case 0:
                add_pin_with_changed_digit(pins, count, observed, i, 8);
                break;
            case 1:
                add_pin_with_changed_digit(pins, count, observed, i, 4);
                add_pin_with_changed_digit(pins, count, observed, i, 2);
                break;
            case 2:
                add_pin_with_changed_digit(pins, count, observed, i, 1);
                add_pin_with_changed_digit(pins, count, observed, i, 5);
                add_pin_with_changed_digit(pins, count, observed, i, 3);
                break;
            case 3:
                add_pin_with_changed_digit(pins, count, observed, i, 2);
                add_pin_with_changed_digit(pins, count, observed, i, 6);
                break;
            case 4:
                add_pin_with_changed_digit(pins, count, observed, i, 1);
                add_pin_with_changed_digit(pins, count, observed, i, 5);
                add_pin_with_changed_digit(pins, count, observed, i, 7);
                break;
            case 5:
                add_pin_with_changed_digit(pins, count, observed, i, 2);
                add_pin_with_changed_digit(pins, count, observed, i, 4);
                add_pin_with_changed_digit(pins, count, observed, i, 6);
                add_pin_with_changed_digit(pins, count, observed, i, 8);
                break;
            case 6:
                add_pin_with_changed_digit(pins, count, observed, i, 3);
                add_pin_with_changed_digit(pins, count, observed, i, 5);
                add_pin_with_changed_digit(pins, count, observed, i, 9);
                break;
            case 7:
                add_pin_with_changed_digit(pins, count, observed, i, 4);
                add_pin_with_changed_digit(pins, count, observed, i, 8);
                break;
            case 8:
                add_pin_with_changed_digit(pins, count, observed, i, 5);
                add_pin_with_changed_digit(pins, count, observed, i, 7);
                add_pin_with_changed_digit(pins, count, observed, i, 9);
                add_pin_with_changed_digit(pins, count, observed, i, 0);
                break;
            case 9:
                add_pin_with_changed_digit(pins, count, observed, i, 6);
                add_pin_with_changed_digit(pins, count, observed, i, 8);
                break;
        }
    }
    

    return pins;
}

void free_pins(char **pins) {
    if (!pins)
        return;
    for (size_t i = 0; i < MAX_PINS; ++i)
        free(pins[i]);
    free(pins);        
}

int main(void) {
    size_t count = 0;
    char **pins = get_pins("123", &count);
    printf("%lu\n", count);
    for (size_t i = 0; i < count; ++i)
        printf("%s\n", pins[i]);
    free_pins(pins);
    printf("\n");
    return 0;
}