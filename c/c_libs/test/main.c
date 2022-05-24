#include <stdio.h>
#include "string_extra.h"

int main(void)
{
    char s[16] = "abcdabcdabcdE";
    printf("%s\n", s);
    char *s2 = strrpl_d(s, "abcd", "ZXCVBN");
    printf("%s\n", s2);
    free(s2);
    return 0;
}
