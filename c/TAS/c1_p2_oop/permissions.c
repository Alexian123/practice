#include <stdlib.h>
#include "permissions.h"

typedef struct _FilePermisions
{
    uint8_t read:1;
    uint8_t write:1;
    uint8_t delete:1;
    uint8_t rename:1;
    uint8_t copy:1;
} FP;


/* 'public' methods -------------- */

FP *__FILE_PERMS__create(uint8_t perms) {
    FP *fp = malloc(sizeof(FP));
    if (!fp)
        return NULL;
    fp->read = fp->write = fp->delete = fp->rename = fp->copy = 0;
    __FILE_PERMS__setPermissions(fp, perms);
    return fp;
}


void __FILE_PERMS__destroy(FP *fp) {
    free(fp);
}

void __FILE_PERMS__setPermissions(FP *fp, uint8_t perms) {
    uint8_t *p = (uint8_t*) fp;
    *p |= perms;
}

void __FILE_PERMS__unsetPermissions(FP *fp, uint8_t perms) {
    uint8_t *p = (uint8_t*) fp;
    *p &= ~perms;
}

uint8_t __FILE_PERMS__checkPermissions(const FP *fp, uint8_t perms) {
    const uint8_t *p = (const uint8_t*) fp;
    return (*p & perms) == perms;
}

/* -------------- */