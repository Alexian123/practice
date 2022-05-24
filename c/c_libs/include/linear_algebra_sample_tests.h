#ifndef __PREMADE_SAMPLE_TESTS_H__
#define __PREMADE_SAMPLE_TESTS_H__

#define VECTOR_NAMESPACE
#define MATRIX_NAMESPACE

#include "matrix.h"
#include "vector.h"

// printing macros (wrappers for print functions)
#define PRINT_VECTOR(VEC) print_vector_components(VEC, #VEC)
#define PRINT_VECTOR_SIZE(VEC) print_vector_size(VEC, #VEC)
#define PRINT_MATRIX(MAT) print_matrix_components(MAT, #MAT)
#define PRINT_MATRIX_SIZE(MAT) print_matrix_size(MAT, #MAT)

// runs all tests
extern int run_sample_tests();

// printing functions
extern void print_vector_components(const VECTOR *v, const char *vec_name);
extern void print_vector_size(const VECTOR *v, const char *vec_name);
extern void print_matrix_components(const MATRIX *m, const char *mat_name);
extern void print_matrix_size(const MATRIX *m, const char *mat_name);

// add elements easily
extern void copy_array_to_vector(VECTOR *v, const double *arr);
extern void copy_array_to_matrix(MATRIX *m, const double *arr);

#endif