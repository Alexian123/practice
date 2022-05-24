#ifndef __RUNTIME_ERRORS_H__
#define __RUNTIME_ERRORS_H__

#include <stdlib.h>

extern void fail_with_msg(const char *format, ...);
extern void fail_with_msg_line(const char *file_name, unsigned int line_number, const char *format, ...);
extern void *xmalloc(size_t size);
extern void *xrealloc(void *ptr, size_t size);

#endif