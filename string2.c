#include <stdio.h>
#include <string.h>

#define MAX_LEN 32

int main(void) {
    unsigned n = 0;
    printf("n = ");
    scanf("%u", &n);

    char buf[MAX_LEN] = "";
    char name[MAX_LEN] = "";
    fgets(buf, MAX_LEN, stdin); // clear stdin buffer
    for (int i = 0; i < n; ++i) {
        fgets(buf, MAX_LEN, stdin);
        buf[strlen(buf) - 1] = '\0';
        if (strlen(buf) > strlen(name)) {
            strncpy(name, buf, MAX_LEN);
        }
    }
    printf("%s - %lu", name, strlen(name));
    printf("\n");
    return 0;
}