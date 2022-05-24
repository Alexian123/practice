#include "logger.h"
#include "runtime_errors.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define MAX_PATH_LEN 256

static struct stat st = { 0 };

FILE *logger_init(const char *file_name)
{
    // create logs dir if !exists
    if (stat(LOGS_DIR, &st) == -1)
        mkdir(LOGS_DIR, 0777);

    char full_path[MAX_PATH_LEN] = "";
    strncpy(full_path, LOGS_DIR, MAX_PATH_LEN);
    strncat(full_path, file_name, MAX_PATH_LEN - (strlen(full_path) + 1));

    FILE *log_file = fopen(full_path, "a");
    if (log_file == NULL)
        fail_with_msg("Error creating logger.");


    // log time and date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    logger_printf(log_file, INFO_LOG, "Entry: %d-%02d-%02d %02d:%02d:%02d\n", 
                  tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
                  tm.tm_hour, tm.tm_min, tm.tm_sec);

    return log_file;
}

int logger_printf(FILE *log_file, enum LOG_LEVEL level, const char *format, ...)
{
    if (log_file == NULL)
        fail_with_msg("Logging failed (NULL file ptr).");

    // print log level
    switch (level) {
        case WARNING_LOG:
            fprintf(log_file, "[WARNING] ");
            break;
        case ERROR_LOG:
            fprintf(log_file, "[ERROR] ");
            break;
        case INFO_LOG:
        default:
            break;
    }

    va_list args;
    int done;

    va_start(args, format);
    done = vfprintf(log_file, format, args);
    va_end(args);

    return done;
}

void logger_end(FILE *log_file)
{
    fclose(log_file);
}