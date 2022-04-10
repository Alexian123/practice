#ifndef __MYTAR_H__
#define __MYTAR_H__

#include <stddef.h>

// values represent bytes
#define BLOCK_SIZE 512
#define NAME_OFFSET 0
#define NAME_LEN 100
#define SIZE_OFFSET 124
#define SIZE_LEN 12
#define CHKSUM_OFFSET 148
#define CHKSUM_LEN 8

void fail_with_msg(const char *msg); // print message and exit with EXIT_FAILURE
void mytar_extract(const char *archive_name); // extract files from archive
void mytar_archive(const char *archive_name, char **file_names, int num_files); // add files to archive
void mytar_print(const char *archive_name); // print contents of archive

#endif