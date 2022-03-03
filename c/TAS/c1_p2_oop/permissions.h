#ifndef __PERMISSIONS_H__
#define __PERMISSIONS_H__

#include <stdint.h>

// possible permissions
#define READ   0x01 // 0000 0001
#define WRITE  0x02 // 0000 0010
#define DELETE 0x04 // 0000 0100
#define RENAME 0x08 // 0000 1000
#define COPY   0x10 // 0001 0000

typedef struct _FilePermisions FILE_PERMS;

// constructor
FILE_PERMS *__FILE_PERMS__create(uint8_t perms);

// destructor
void __FILE_PERMS__destroy(FILE_PERMS *fp);

// methods
void __FILE_PERMS__setPermissions(FILE_PERMS *fp, uint8_t perms);
void __FILE_PERMS__unsetPermissions(FILE_PERMS *fp, uint8_t perms);
uint8_t __FILE_PERMS__checkPermissions(const FILE_PERMS *fp, uint8_t perms);

#endif