#include "linear_algebra_sample_tests.h"
#include "simple_tests.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#define NUM_TESTS 6

// tests
static enum TEST_RESULT vector_print_test(void);
static enum TEST_RESULT vector_operations_test(void);
static enum TEST_RESULT linear_transformation_test(void);
static enum TEST_RESULT matrix_print_test(void);
static enum TEST_RESULT matrix_operations_test(void);
static enum TEST_RESULT determinant_test(void);

// tests are added here (manually)
static const enum TEST_RESULT (*TEST_FUNCS[NUM_TESTS])(void) = {
    vector_print_test,
    matrix_print_test,
    vector_operations_test,
    matrix_operations_test,
    linear_transformation_test,
    determinant_test,
};

// test names are added here (manually)
static char TEST_NAMES[NUM_TESTS][MAX_TEST_NAME_LENGTH] = {
    "V print test",
    "M print test",
    "V op test",
    "M op test",
    "Linear transformation test",
    "Determinant test",
};

// set by init function
static struct TEST tests[NUM_TESTS];

// make sure init is only called once
static bool IS_INIT = false;

// initialize tests (called automatically by run function)
static void sample_tests_init();

// pthread function
static void *make_first_half_of_tests(void *tests); // pthread function


enum TEST_RESULT determinant_test(void)
{
    MATRIX *m = MATRIX_METHODS.create(7, 7);
    double arr[49] = {1, 2, 3, 4, 5, 6, 7,
                      1, 7, 4, 2, 11, -4, 1,
                      0, -9, 4, -9, 0, 3, 2,
                      3, 5, 1, -2, 3, 3, 3,
                      20, 15, 0, -7, -7, 19, 11,
                      -21, -23, 6, 3, 5, 7, -55,
                      -22, 51, 2, 4, 6, 8, 3};
    
    copy_array_to_matrix(m, arr);
    PRINT_MATRIX_SIZE(m);
    PRINT_MATRIX(m);

    printf("\ndet = %lf\n", MATRIX_METHODS.determinant(m));

    MATRIX_METHODS.destroy(m);

    return TEST_SUCCESS;
}

enum TEST_RESULT matrix_print_test(void)
{
    MATRIX *m = MATRIX_METHODS.create(5, 1);
    double arr[20] = {1, 2048, -3, 4,  
                      6, 7, 8, 9, 
                      11, 12, 13, 14,  
                      16, 17, 18, 19};
    copy_array_to_matrix(m, arr);
    PRINT_MATRIX_SIZE(m);
    PRINT_MATRIX(m);
    MATRIX_METHODS.destroy(m);

    return TEST_SUCCESS;
}

enum TEST_RESULT matrix_operations_test(void)
{
    MATRIX *m1 = MATRIX_METHODS.create(4, 4);
    double arr1[20] = {1, 2, 3, 5,  
                      1, -1, 10, 0.1,
                      1, 0, 1, 14,  
                      16, 17, 18, 19};
    MATRIX *m2 = MATRIX_METHODS.create(4, 4);
    double arr2[20] = {-1, 7, 6, 4,  
                      1, 1, 0, 9, 
                      -6, 8, 0.5, 14,  
                      16, 17, 18, 19};
    
    MATRIX *m3 = MATRIX_METHODS.create(4, 4);

    copy_array_to_matrix(m1, arr1);
    copy_array_to_matrix(m2, arr2);

    PRINT_MATRIX(m1);
    PRINT_MATRIX(m2);

    MATRIX_METHODS.makeIdentityMatrix(m1);
    MATRIX_METHODS.multiply(m1, m2, m3);
    PRINT_MATRIX(m3);

    MATRIX_METHODS.scaleBy(m2, -2);
    PRINT_MATRIX(m2);

    MATRIX_METHODS.subtract(m1, m2, m3);

    PRINT_MATRIX(m3);

    MATRIX_METHODS.destroy(m1);
    MATRIX_METHODS.destroy(m2);
    MATRIX_METHODS.destroy(m3);

    return TEST_SUCCESS;
}

enum TEST_RESULT linear_transformation_test(void)
{
    VECTOR *v = VECTOR_METHODS.create(3);
    double vcomps[] = {1, 2, 3};
    copy_array_to_vector(v, vcomps);
    PRINT_VECTOR(v);

    MATRIX *m = MATRIX_METHODS.create(4, 3);
    double mcomps[] = {1, 2, -1,
                       3, 1, 0,
                       0, -1, 1,
                       -2, 1, 1};
    copy_array_to_matrix(m, mcomps);
    PRINT_MATRIX(m);

    VECTOR_METHODS.applyTransformation(&v, m);
    PRINT_VECTOR(v);

    VECTOR_METHODS.destroy(v);
    MATRIX_METHODS.destroy(m);

    return TEST_SUCCESS;
}

enum TEST_RESULT vector_print_test(void)
{
    VECTOR *o = NULL;

    VECTOR *v = VECTOR_METHODS.create(1);
    VECTOR_METHODS.setComp(v, 0, -7);

    VECTOR *w = VECTOR_METHODS.create(2);
    VECTOR_METHODS.setComp(w, 0, 5);
    VECTOR_METHODS.setComp(w, 1, 100);

    VECTOR *p = VECTOR_METHODS.create(3);
    VECTOR_METHODS.setComp(p, 0, 3.1579);
    VECTOR_METHODS.setComp(p, 1, -17.001);
    VECTOR_METHODS.setComp(p, 2, 0);

    VECTOR *q = VECTOR_METHODS.create(8);
    double arr[] = {0, 1, 0, 0, 0, 0, 0, 0};
    copy_array_to_vector(q, arr);

    PRINT_VECTOR_SIZE(v);
    PRINT_VECTOR(v);

    PRINT_VECTOR_SIZE(w);
    PRINT_VECTOR(w);

    PRINT_VECTOR_SIZE(p);
    PRINT_VECTOR(p);

    PRINT_VECTOR_SIZE(q);
    PRINT_VECTOR(q);

    VECTOR_METHODS.destroy(o);
    VECTOR_METHODS.destroy(v);
    VECTOR_METHODS.destroy(w);
    VECTOR_METHODS.destroy(p);
    VECTOR_METHODS.destroy(q);

    return TEST_SUCCESS;
}

enum TEST_RESULT vector_operations_test(void)
{
    VECTOR* v1 = VECTOR_METHODS.create(3);
    VECTOR* v2 = VECTOR_METHODS.create(3);
    VECTOR* v3 = VECTOR_METHODS.create(3);
    VECTOR* null = VECTOR_METHODS.create(3);

    double arr1[] = {1, 2, 3}, arr2[] = {-1, -2, -3};
    
    copy_array_to_vector(v1, arr1);
    copy_array_to_vector(v2, arr2);

    PRINT_VECTOR(v1);
    PRINT_VECTOR(v2);
    PRINT_VECTOR(null);

    printf("v1 norm = %lf\n", VECTOR_METHODS.getNorm(v1));
    printf("v2 norm = %lf\n", VECTOR_METHODS.getNorm(v2));
    printf("null norm = %lf\n", VECTOR_METHODS.getNorm(null));

    printf("<v1, v2> = %lf\n", VECTOR_METHODS.stdDotProduct(v1, v2));

    VECTOR_METHODS.add(v1, v2, v3);
    printf("v1 + v2 = v3\n");
    PRINT_VECTOR(v3);

    VECTOR_METHODS.subtract(v1, v2, v3);
    printf("v1 - v2 = v3\n");
    PRINT_VECTOR(v3);

    printf("are v1 and v2 orthogonal: %d\n", VECTOR_METHODS.areOrthogonal(v1, v2));

    VECTOR_METHODS.project(v1, v2, v3);
    PRINT_VECTOR(v3);

    printf("cos(v1, v2) = %lf\n", VECTOR_METHODS.getCosine(v1, v2));

    VECTOR_METHODS.destroy(v1);
    VECTOR_METHODS.destroy(v2);
    VECTOR_METHODS.destroy(v3);
    VECTOR_METHODS.destroy(null);

    return TEST_SUCCESS;
}


int run_sample_tests()
{
    if (!IS_INIT) {
        sample_tests_init();
        IS_INIT = true;
    }
    int status = simple_tests_run_multiple(tests, NUM_TESTS);
    simple_tests_end(); 
    return status;
}

void sample_tests_init()
{
    // initialize test framework
    simple_tests_init(); 

    // create first half of tests on separate thread
    pthread_t new_thread;
    pthread_create(&new_thread, NULL, make_first_half_of_tests, tests);

    // create second half of tests on main thread
    for (size_t i = NUM_TESTS / 2; i < NUM_TESTS; ++i)
        tests[i] = simple_tests_make(TEST_FUNCS[i], TEST_NAMES[i]);

    // wait for both threads to finish
    pthread_join(new_thread, NULL);
}

void *make_first_half_of_tests(void *tests) // pthread function
{
    if (tests != NULL) {
        for (size_t i = 0; i < NUM_TESTS / 2; ++i)
            *((struct TEST*) tests + i) = simple_tests_make(TEST_FUNCS[i], TEST_NAMES[i]);
    }
    return NULL;
}


void copy_array_to_vector(VECTOR *v, const double *arr)
{
    size_t n = VECTOR_METHODS.getSize(v);
    for (size_t i = 0; i < n; ++i)
        VECTOR_METHODS.setComp(v, i, arr[i]);
}

void copy_array_to_matrix(MATRIX *m, const double *arr)
{
    size_t rows = MATRIX_METHODS.getNumOfRows(m);
    size_t cols = MATRIX_METHODS.getNumOfCols(m);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            MATRIX_METHODS.setComp(m, i, j, arr[i * cols + j]);
}


void print_vector_components(const VECTOR *v, const char *vec_name)
{
    if (v == NULL)
        return;
    size_t n = VECTOR_METHODS.getSize(v);
    if (n == 1) {
        printf("%s = (%.2lf)\n", vec_name, VECTOR_METHODS.getComp(v, 0));
        return;
    }
    printf("%s = (%.2lf,", vec_name, VECTOR_METHODS.getComp(v, 0));
    for (size_t i = 1; i < n - 1; ++i)
        printf("%7.2lf,", VECTOR_METHODS.getComp(v, i));
    printf("%7.2lf)\n", VECTOR_METHODS.getComp(v, n - 1));
}

void print_vector_size(const VECTOR *v, const char *vec_name)
{
    printf("size of %s: %lu\n", vec_name, VECTOR_METHODS.getSize(v));
}

void print_matrix_components(const MATRIX *m, const char *mat_name)
{
    if (m == NULL)
        return;
    size_t rows = MATRIX_METHODS.getNumOfRows(m);
    size_t cols = MATRIX_METHODS.getNumOfCols(m);
    if (rows == 1 && cols == 1) {
        printf("%s = [%7.2lf]\n", mat_name, MATRIX_METHODS.getComp(m, 0, 0));
        return;
    }
    if (rows == 1) {
        printf("%s = [%7.2lf", mat_name, MATRIX_METHODS.getComp(m, 0, 0));
        for (size_t j = 1; j < cols - 1; ++j)
            printf("%7.2lf", MATRIX_METHODS.getComp(m, 0, j));
        printf("%7.2lf]\n", MATRIX_METHODS.getComp(m, 0, cols - 1));
        return;
    }
    printf("%s =\n", mat_name);
    if (cols == 1) {
        for (size_t i = 0; i < rows; ++i)
            printf("[%-7.2lf]\n", MATRIX_METHODS.getComp(m, i, 0));
        printf("\n");
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        printf("[%-7.2lf", MATRIX_METHODS.getComp(m, i, 0));
        for (size_t j = 1; j < cols - 1; ++j)
            printf("%7.2lf", MATRIX_METHODS.getComp(m, i, j));
        printf("%7.2lf]\n", MATRIX_METHODS.getComp(m, i, cols - 1));
    }
    printf("\n");
}

void print_matrix_size(const MATRIX *m, const char *mat_name)
{
    printf("matrix %s is %lu by %lu\n", mat_name, MATRIX_METHODS.getNumOfRows(m), MATRIX_METHODS.getNumOfCols(m));
}