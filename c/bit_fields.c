#include <stdio.h>

typedef unsigned char u8;

int main(void) {

    struct Field
    {
        u8 b0:1;
        u8 b1:1;
        u8 b2:1;
        u8 b3:1;
        u8 b4:1;
        u8 b5:1;
        u8 b6:1;
        u8 b7:1;
    } myField;

    u8 *field = (u8*) &myField;
    *field &= 0;

    for (int i = 4; i < 8; ++i) {
        *field |= (1 << i);
    }

    printf("%d ", myField.b0);
    printf("%d ", myField.b1);
    printf("%d ", myField.b2);
    printf("%d ", myField.b3);
    printf("%d ", myField.b4);
    printf("%d ", myField.b5);
    printf("%d ", myField.b6);
    printf("%d ", myField.b7);

    printf("\n");
    return 0;
}