#include <stdio.h>
#include "permissions.h"


int main(void) {
    FILE_PERMS *user = __FILE_PERMS__create();
    __FILE_PERMS__setPermission(user, READ);
    __FILE_PERMS__setPermission(user, WRITE);
    __FILE_PERMS__setPermission(user, COPY);
    __FILE_PERMS__setPermission(user, DELETE);
    __FILE_PERMS__unsetPermission(user, READ);
    __FILE_PERMS__unsetPermission(user, COPY);
    printf("%u\n", __FILE_PERMS__checkPermission(user, WRITE));
    printf("%u", __FILE_PERMS__checkPermission(user, DELETE));
    __FILE_PERMS__destroy(user);

    printf("\n");
    return 0;
}