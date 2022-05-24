#include "runtime_errors.h"

#include <error.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define MAX_MSG_LENGTH 256
 
// convert format and va_list to formated string
static char msg[MAX_MSG_LENGTH] = "";
static int get_formated_msg(const char *fmt, va_list args);

void fail_with_msg(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    get_formated_msg(format, args);
    va_end(args);
    error(EXIT_FAILURE, 0, "%s", msg);
}

void fail_with_msg_line(const char *file_name, unsigned int line_number, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    get_formated_msg(format, args);
    va_end(args);
    error_at_line(EXIT_FAILURE, 0, file_name, line_number, "%s", msg);
}

void *xmalloc(size_t size)
{
    void *p = malloc(size);
    if (p == NULL)
        fail_with_msg("Malloc error.");
    return p;
}

void *xrealloc(void *ptr, size_t size)
{
    void *p = realloc(ptr, size);
    if (p == NULL)
        fail_with_msg("Realloc error.");
    return p;
}

int get_formated_msg(const char *fmt, va_list args)
{
    return vsnprintf(msg, MAX_MSG_LENGTH, fmt, args);
}