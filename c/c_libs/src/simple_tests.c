#include "simple_tests.h"
#include "runtime_errors.h"
#include "logger.h"

#include <stdio.h>
#include <string.h>

#define LOG_FILE_NAME "tests.log"

static FILE *log_file = NULL;

static size_t passed = 0;
static size_t failed = 0;

void simple_tests_init()
{
    log_file = logger_init(LOG_FILE_NAME);
}

void simple_tests_end()
{
    logger_end(log_file);
}

struct TEST simple_tests_make(enum TEST_RESULT (*func)(void), const char *name)
{
    struct TEST new_test;
    new_test.__function = func;
    strncpy(new_test.__name, name, MAX_TEST_NAME_LENGTH);
    return new_test;
}

int simple_tests_run(struct TEST t)
{
    enum TEST_RESULT r = t.__function();
    switch (r) {
        case TEST_SUCCESS:
            logger_printf(log_file, INFO_LOG, "+++ %s passed +++\n", t.__name);
            ++passed;
            break;
        case TEST_FAILURE:
            logger_printf(log_file, WARNING_LOG, "!!! %s failed !!!\n", t.__name);
            ++failed;
            break;
        default:
            logger_printf(log_file, WARNING_LOG, "??? Unknown result for %s ???\n", t.__name);
    }
    return r;
}

int simple_tests_run_multiple(struct TEST tests[], size_t n)
{
    if (tests == NULL) {
        logger_printf(log_file, ERROR_LOG, "Null pointer to tests.");
        fail_with_msg("Error running tests.");
    }

    logger_printf(log_file, INFO_LOG, "=== Running tests ===\n\n");

    // reset stats
    passed = failed = 0;

    for (size_t i = 0; i < n; ++i) {
        if (tests[i].__function == NULL) {
            logger_printf(log_file, ERROR_LOG, "Error running test #%zu.\n\n", i);
            continue;
        }
        logger_printf(log_file, INFO_LOG, "\n--- Running test #%zu ---\n\n", i);
        simple_tests_run(tests[i]);
        logger_printf(log_file, INFO_LOG, "\n--- End of test #%zu ---\n\n", i);
    }

    logger_printf(log_file, INFO_LOG, "\n <<< Stats >>>\n");
    logger_printf(log_file, INFO_LOG, "%zu/%zu passed\n", passed, n);
    logger_printf(log_file, INFO_LOG, "%zu/%zu failed\n", failed, n);
    logger_printf(log_file, INFO_LOG, "\n=== Finished running tests ===\n\n");

    return failed;
}