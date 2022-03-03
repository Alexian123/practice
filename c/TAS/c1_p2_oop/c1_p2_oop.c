#include <stdio.h>
#include "permissions.h"


int main(void) {
    FILE_PERMS *user = __FILE_PERMS__create(READ | WRITE | COPY | DELETE);
    __FILE_PERMS__unsetPermissions(user, READ | COPY);
    printf("%hhu", __FILE_PERMS__checkPermissions(user, DELETE | WRITE));
    __FILE_PERMS__destroy(user);

    printf("\n");
    return 0;
}