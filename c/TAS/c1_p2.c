#include <stdio.h>
#include <stdint.h>

// possible permissions
#define READ   0x01 // 0000 0001
#define WRITE  0x02 // 0000 0010
#define DELETE 0x04 // 0000 0100
#define RENAME 0x08 // 0000 1000
#define COPY   0x10 // 0001 0000

void set_permissions(uint8_t *user, uint8_t perms) {
    *user |= perms;
}

void unset_permissions(uint8_t *user, uint8_t perms) {
    *user &= ~perms;
}

uint8_t check_permisions(uint8_t user, uint8_t perms) {
    return (user & perms) == perms;
}

int main(void) {
    uint8_t user1 = 0;
    set_permissions(&user1, READ | WRITE | COPY | DELETE);
    unset_permissions(&user1, READ | COPY);
    printf("%hhu", check_permisions(user1, WRITE | DELETE)); 
    printf("\n");
    return 0;
}