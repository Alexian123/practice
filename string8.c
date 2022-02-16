#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

int main(void) {
    char s1[] = "Zi o propozitie Adi: Iova suge pula! suge Suge sugepula";
    char s2[] = "suge";

    char aux[MAX_LEN] = "";
    const char sep[] = " .,:;!?\n\t\v\r";
    strncpy(aux, s1, MAX_LEN);

    char *p = NULL;
    p = strstr(s1, s2);
    while (p) {
        for (int i = 0; i < strlen(s2); ++i) {
            p[i] = toupper(p[i]);
        }
        p = strstr(p + strlen(s2), s2);
    }
    printf("%s\n", s1);

    unsigned count = 0;
    p = strtok(aux, sep);
    while (p) {
        ++count;
        printf("%s\n", p);
        p = strtok(NULL, sep);
    }
    printf("%u\n", count);
    return 0;
}