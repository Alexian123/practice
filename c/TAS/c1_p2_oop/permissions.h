#ifndef __PERMISSIONS_H__
#define __PERMISSIONS_H__

typedef struct _FilePermisions FILE_PERMS;

enum Permission
{
    READ,
    WRITE,
    DELETE,
    RENAME,
    COPY
};

// constructor
FILE_PERMS *__FILE_PERMS__create();

// destructor
void __FILE_PERMS__destroy(FILE_PERMS *fp);

// methods
void __FILE_PERMS__setPermission(FILE_PERMS *fp, enum Permission perm);
void __FILE_PERMS__unsetPermission(FILE_PERMS *fp, enum Permission perm);
unsigned char __FILE_PERMS__checkPermission(const FILE_PERMS *fp, enum Permission perm);

#endif