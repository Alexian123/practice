#ifndef __SIMPLE_TESTS_H__
#define __SIMPLE_TESTS_H__

#include <stdlib.h>

#define MAX_TEST_NAME_LENGTH 256

enum TEST_RESULT
{
    TEST_SUCCESS = 1,
    TEST_FAILURE = -1
};

struct TEST
{
    enum TEST_RESULT (*__function)(void);
    char __name[MAX_TEST_NAME_LENGTH];
};

// call before running any tests
extern void simple_tests_init();

// call after running all tests
extern void simple_tests_end();

extern struct TEST simple_tests_make(enum TEST_RESULT (*func)(void), const char *name);

// return test results
extern int simple_tests_run(struct TEST t);
extern int simple_tests_run_multiple(struct TEST tests[], size_t num_tests);

#endif