#include <stdlib.h>
#include "permissions.h"

#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct _FilePermisions
{
    boolean read:1;
    boolean write:1;
    boolean delete:1;
    boolean rename:1;
    boolean copy:1;
} FP;


/* 'public' methods -------------- */

FP *__FILE_PERMS__create() {
    FP *fp = malloc(sizeof(FP));
    if (!fp)
        return NULL;
    fp->read = fp->write = fp->delete = fp->rename = fp->copy = FALSE;
    return fp;
}


void __FILE_PERMS__destroy(FP *fp) {
    free(fp);
}

void __FILE_PERMS__setPermission(FP *fp, enum Permission perm) {
    if (!fp)
        return;
    switch (perm) {
        case READ:
            fp->read = TRUE;
            break;
        case WRITE:
            fp->write = TRUE;
            break;
        case DELETE:
            fp->delete = TRUE;
            break;
        case RENAME:
            fp->rename = TRUE;
            break;
        case COPY:
            fp->copy = TRUE;
            break;
    } 
}

void __FILE_PERMS__unsetPermission(FP *fp, enum Permission perm) {
    if (!fp)
        return;
    switch (perm) {
        case READ:
            fp->read = FALSE;
            break;
        case WRITE:
            fp->write = FALSE;
            break;
        case DELETE:
            fp->delete = FALSE;
            break;
        case RENAME:
            fp->rename = FALSE;
            break;
        case COPY:
            fp->copy = FALSE;
            break;
    } 
}

boolean __FILE_PERMS__checkPermission(const FP *fp, enum Permission perm) {
    if (!fp)
        return FALSE;
    switch (perm) {
        case READ:
            return fp->read;
        case WRITE:
            return fp->write;
        case DELETE:
            return fp->delete;
        case RENAME:
            return fp->rename;
        case COPY:
            return fp->copy;
        default:
            return FALSE;
    } 
}

/* -------------- */