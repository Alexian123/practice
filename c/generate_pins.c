#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define END_PIN "X" // marks end of pins array (for cleanup function)

/* - the first column represents the number of elements in each row;
   - the remaining columns contain a digit and all adjancet digits on the keypad;
   - the row index corresponds to each possibile digit (second column);
   eg: keys[6] = {5, 6, 3, 5, 9} where 5 is the number of elements,
   6 is the digit corresponding to the index and 3,5,9 are digits adjancet to 6.
*/
static const int keys[10][6] = { {3, 0, 8}, 
                                 {4, 1, 2, 4}, 
                                 {5, 2, 1, 5, 3}, 
                                 {4, 3, 2, 6}, 
                                 {5, 4, 1, 5, 7},
                                 {6, 5, 2, 4, 8, 6}, 
                                 {5, 6, 3, 5, 9}, 
                                 {4, 7, 4, 8}, 
                                 {6, 8, 5, 7, 0, 9}, 
                                 {4, 9, 6, 8} };

size_t pow_unsigned(size_t base, size_t exponent) {
    size_t result = 1;
    for (size_t i = 0; i < exponent; ++i)
        result *= base;
    return result;
}

void generate_pins_1_digit(char **pins, size_t *count, const int *digits);
void generate_pins_2_digit(char **pins, size_t *count, const int *digits);
void generate_pins_3_digit(char **pins, size_t *count, const int *digits);
void generate_pins_4_digit(char **pins, size_t *count, const int *digits);
void generate_pins_5_digit(char **pins, size_t *count, const int *digits);
void generate_pins_6_digit(char **pins, size_t *count, const int *digits);
void generate_pins_7_digit(char **pins, size_t *count, const int *digits);
void generate_pins_8_digit(char **pins, size_t *count, const int *digits);

// will assume malloc won't ever fail for simplicity
char **get_pins(const char *observed, size_t *count) {
    *count = 0;
    size_t len = strlen(observed);
    // allocate for max num of possible pins 
    size_t max_pins = pow_unsigned(5, len); // 5 and 8 have 4 adjacent digits, so 5 cases in total
    char **pins = malloc(sizeof(char*) * (max_pins + 1)); // +1 for END_PIN
    for (size_t i = 0; i < max_pins + 1; ++i) {
        pins[i] = malloc(len + 1);
        memset(pins[i], 0, len + 1);
    }
    strcpy(pins[max_pins], END_PIN); // set END_PIN

    // copy the observed pin's digits into an array
    int *digits = malloc(len * sizeof(int));
    for (size_t i = 0; i < len; ++i)
        digits[i] = observed[i] - '0';

    // iterate through each digit and its adjancet digits (will also generate the observed pin)
    // the number of digits corresponds to the number of nested loops required
    switch (len) {
        case 1: generate_pins_1_digit(pins, count, digits); break;
        case 2: generate_pins_2_digit(pins, count, digits); break;
        case 3: generate_pins_3_digit(pins, count, digits); break;
        case 4: generate_pins_4_digit(pins, count, digits); break;
        case 5: generate_pins_5_digit(pins, count, digits); break;
        case 6: generate_pins_6_digit(pins, count, digits); break;
        case 7: generate_pins_7_digit(pins, count, digits); break;
        case 8: generate_pins_8_digit(pins, count, digits); break;
        default:    break;
    }

    free(digits);
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

void generate_pins_1_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        sprintf(pins[(*count)++], "%d", keys[digits[0]][i]);
}

void generate_pins_2_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            sprintf(pins[(*count)++], "%d%d", keys[digits[0]][i], 
                                              keys[digits[1]][j]);
}

void generate_pins_3_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            for (size_t k = 1; k < keys[digits[2]][0]; ++k)
                sprintf(pins[(*count)++], "%d%d%d", keys[digits[0]][i], 
                                                    keys[digits[1]][j], 
                                                    keys[digits[2]][k]);
}

void generate_pins_4_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            for (size_t k = 1; k < keys[digits[2]][0]; ++k)
                for (size_t l = 1; l < keys[digits[3]][0]; ++l)
                    sprintf(pins[(*count)++], "%d%d%d%d", keys[digits[0]][i], 
                                                          keys[digits[1]][j], 
                                                          keys[digits[2]][k], 
                                                          keys[digits[3]][l]);
}

void generate_pins_5_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            for (size_t k = 1; k < keys[digits[2]][0]; ++k)
                for (size_t l = 1; l < keys[digits[3]][0]; ++l)
                    for (size_t h = 1; h < keys[digits[4]][0]; ++h)
                        sprintf(pins[(*count)++], "%d%d%d%d%d", keys[digits[0]][i], 
                                                                keys[digits[1]][j], 
                                                                keys[digits[2]][k], 
                                                                keys[digits[3]][l], 
                                                                keys[digits[4]][h]);
}

void generate_pins_6_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            for (size_t k = 1; k < keys[digits[2]][0]; ++k)
                for (size_t l = 1; l < keys[digits[3]][0]; ++l)
                    for (size_t h = 1; h < keys[digits[4]][0]; ++h)
                        for (size_t z = 1; z < keys[digits[5]][0]; ++z)
                            sprintf(pins[(*count)++], "%d%d%d%d%d%d", keys[digits[0]][i], 
                                                                      keys[digits[1]][j], 
                                                                      keys[digits[2]][k], 
                                                                      keys[digits[3]][l], 
                                                                      keys[digits[4]][h], 
                                                                      keys[digits[5]][z]);
}

void generate_pins_7_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            for (size_t k = 1; k < keys[digits[2]][0]; ++k)
                for (size_t l = 1; l < keys[digits[3]][0]; ++l)
                    for (size_t h = 1; h < keys[digits[4]][0]; ++h)
                        for (size_t z = 1; z < keys[digits[5]][0]; ++z)
                            for (size_t x = 1; x < keys[digits[6]][0]; ++x)
                                sprintf(pins[(*count)++], "%d%d%d%d%d%d%d", keys[digits[0]][i], 
                                                                            keys[digits[1]][j], 
                                                                            keys[digits[2]][k], 
                                                                            keys[digits[3]][l], 
                                                                            keys[digits[4]][h], 
                                                                            keys[digits[5]][z], 
                                                                            keys[digits[6]][x]);
}

void generate_pins_8_digit(char **pins, size_t *count, const int *digits) {
    for (size_t i = 1; i < keys[digits[0]][0]; ++i)
        for (size_t j = 1; j < keys[digits[1]][0]; ++j)
            for (size_t k = 1; k < keys[digits[2]][0]; ++k)
                for (size_t l = 1; l < keys[digits[3]][0]; ++l)
                    for (size_t h = 1; h < keys[digits[4]][0]; ++h)
                        for (size_t z = 1; z < keys[digits[5]][0]; ++z)
                            for (size_t x = 1; x < keys[digits[6]][0]; ++x)
                                for (size_t c = 1; c < keys[digits[7]][0]; ++c)
                                    sprintf(pins[(*count)++], "%d%d%d%d%d%d%d%d", keys[digits[0]][i], 
                                                                                  keys[digits[1]][j], 
                                                                                  keys[digits[2]][k], 
                                                                                  keys[digits[3]][l], 
                                                                                  keys[digits[4]][h], 
                                                                                  keys[digits[5]][z], 
                                                                                  keys[digits[6]][x], 
                                                                                  keys[digits[7]][c]);
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