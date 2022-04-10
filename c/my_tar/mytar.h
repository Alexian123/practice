#ifndef __MYTAR_H__
#define __MYTAR_H__

#include <stddef.h>

// print message and exit with EXIT_FAILURE
void fail_with_msg(const char *msg);

// extract files from archive
void mytar_extract(const char *archive_name);

// add files to archive
void mytar_archive(const char *archive_name, char **file_names, int num_files);

// print contents of archive
void mytar_print(const char *archive_name);

#endif