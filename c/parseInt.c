#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// handle numbers 0 to 19
int32_t parse_int_single_word_number(const char *number) {
    static const char *NUMS[] = {"zero", "one", "two", "three", "four", 
                                  "five", "six", "seven", "eight", "nine",
                                  "ten", "eleven", "twelve", "thirteen", "fourteen",
                                  "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    for (int32_t i = 0; i < sizeof(NUMS) / sizeof(NUMS[0]); ++i) {
        if (strcmp(number, NUMS[i]) == 0)
            return i;
    }
    return -1; // number is greater than 19
}

// handle numbers 20 to 99
int32_t parse_int_2_digits(const char *number) {
    static const char *MULTIPLES[] = {"twenty", "thirty", "forty", "fifty", "sixty", 
                                 "seventy", "eighty", "ninety"};
    static size_t N = sizeof(MULTIPLES) / sizeof(MULTIPLES[0]);

    char *dash_addr = strchr(number, '-');

    // check if number is a multiple of 10
    if (!dash_addr) {
        for (int32_t i = 0; i < N; ++i) {
            if (strcmp(number, MULTIPLES[i]) == 0)
                return (i + 2) * 10;
        }
    }

    // parse 10s
    int32_t a = 0;
    for (int32_t i = 0; i < N; ++i) {
        if (strstr(number, MULTIPLES[i])) {
            a = i + 2;
            break;
        }
    }

    // parse units
    int32_t b = parse_int_single_word_number(dash_addr + 1);

    return a*10 + b;
}

// handle numbers 0 to 99
int32_t parse_int_0_to_99(const char *number) {
    int32_t num = parse_int_single_word_number(number);
    if (num != -1) // number is between 0 and 19
        return num;
    // number is between 20 and 99
    return parse_int_2_digits(number);
}

// handle numbers 100 to 999
int32_t parse_int_3_digits(const char *number) {
    char *num = strdup(number);
    if (!num)
        return -1; // malloc error

    // parse 100s (the first word)
    static const char sep[] = " ";
    char *token = strtok(num, sep);
    int32_t a = parse_int_single_word_number(token); 

    // the next word will be "hundred", so we can ignore it
    token = strtok(NULL, sep);

    token = strtok(NULL, sep);
    if (!token) // there are no more words
        return a*100;

    // check if there is an "and" and ignore it
    if (strcmp(token, "and") == 0)
        token = strtok(NULL, sep);

    // token should now be a number between 1 and 99
    int32_t b = parse_int_0_to_99(token);

    free(num);
    return a*100 + b;
}

// handle numbers 0 to 999
int32_t parse_int_0_to_999(const char *number) {
    // check number is between 0 and 99 (single word)
    if (!strchr(number, ' '))
        return parse_int_0_to_99(number);
    // number is between 100 and 999
    return parse_int_3_digits(number);
}

int32_t parse_int(const char *number) {
    // check if number is 1 mil (max number possible)
    if (strcmp(number, "one million") == 0)
        return 1000000;

    // check if number is between 0 and 999
    char *thou_addr = strstr(number, "thousand");
    if (!thou_addr)
        return parse_int_0_to_999(number);
    
    // if we got here, our number is betwenn 1000 and 999999
    int32_t a = 0, b = 0;

    // parse 1000s
    char *num = strndup(number, thou_addr - number - 1);
    if (!num)
        return -1; // malloc error
    a = parse_int_0_to_999(num);
    free(num);

    // check if anything left to parse
    size_t len_thousand = strlen("thousand");
    if (*(thou_addr + len_thousand) == '\0') { // nothing left
        return a*1000;
    }

    // ignore "thousand "
    num = strdup(thou_addr + len_thousand + 1);  
    if (!num)
        return -1; // malloc error

    // ignore "and "
    if (strncmp(num, "and", strlen("and")) == 0) 
        strcpy(num, num + strlen("and") + 1);
    
    // parse 100s
    b = parse_int_0_to_999(num);
    free(num);

    return a*1000 + b;
}

int main(void) {

    printf("%d", parse_int("nine hundred and sixty-five thousand and three hundred twenty-nine"));

    printf("\n");
    return 0;
}