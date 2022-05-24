#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

#define LOGS_DIR "./logs/"

enum LOG_LEVEL
{
    INFO_LOG = 0,
    WARNING_LOG = 1,
    ERROR_LOG = 2,
};

// must be called first
extern FILE *logger_init(const char *file_name);

// similar to printf
extern int logger_printf(FILE *log_file, enum LOG_LEVEL level, const char *format, ...);

// call when logger is no longer needed
extern void logger_end(FILE *log_file);

#endif