#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// key = <name of time unit>, val = <no of units>, priority = <5,4,3,2,1 ~ year,day,hour,min,sec>
struct key_val
{
    char key[7];
    int val;
    int priority;
};

// for qsort
int comp_val(const void *a, const void *b) {
    return ((struct key_val*) a)->val < ((struct key_val*) b)->val;
}

// for qsort
int comp_priority(const void *a, const void *b) {
    return ((struct key_val*) a)->priority < ((struct key_val*) b)->priority;
}

// we will assume malloc does not fail for simplicity
char *formatDuration(int n) {
    // constants
    static const int secs_per_min = 60,
                     mins_per_hour = 60,
                     hours_per_day = 24,
                     days_per_year = 365;

    // output string
    char *str = malloc(64);
    strcpy(str, "");

    // check 0 seconds case
    if (n == 0) {
        strcpy(str, "now");
        return str;
    }

    // store time as an array of key_val
    struct key_val time[] = { {"year", 0, 5}, {"day", 0, 4}, {"hour", 0, 3}, 
                              {"minute", 0, 2}, {"second", 0, 1} };
    size_t len = sizeof(time) / sizeof(time[0]);
    
    // calculate years, days, hours, minutes and seconds
    time[4].val = n;
    time[3].val = time[4].val / secs_per_min;
    time[4].val %= secs_per_min;
    time[2].val = time[3].val / mins_per_hour;
    time[3].val %= mins_per_hour;
    time[1].val = time[2].val / hours_per_day;
    time[2].val %= hours_per_day;
    time[0].val = time[1].val / days_per_year;
    time[1].val %= days_per_year;

    // set key to plural form where needed and count non-zero values
    size_t count = 0;
    for (size_t i = 0; i < len; ++i) {
        count += (time[i].val != 0);
        if (time[i].val > 1)
            strcat(time[i].key, "s");
    }

    // sort the array in descending order to have the non-zero values first
    qsort(time, sizeof(time) / sizeof(time[0]), sizeof(time[0]), comp_val);
    
    // sort the non-zero values in descending order of priority
    qsort(time, count, sizeof(time[0]), comp_priority);

    char buf[32] = ""; // buffer to store numbers as strings
    sprintf(buf, "%d %s", time[0].val, time[0].key);
    strcat(str, buf);

    for (size_t i = 1; i < count - 1; ++i) {
        sprintf(buf, ", %d %s", time[i].val, time[i].key);
        strcat(str, buf);
    }

    if (count > 1) {
        sprintf(buf, " and %d %s", time[count - 1].val, time[count - 1].key);
        strcat(str, buf);
    }

    return str;
}

int main(void) {
    char *s = formatDuration(3662);
    printf("%s", s);
    printf("\n");
    return 0;
}