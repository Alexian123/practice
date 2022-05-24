#include "matrix.h"
#include "vector.h"
#include "runtime_errors.h"

#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define EXPORT_DIR "./export/"
#define MAX_PATH_LEN 256

// struct with private members
typedef struct __Mat
{
    double *comp;
    size_t rows;
    size_t cols;
} M;

/* private methods */
static bool are_the_same_size_3(const M *m1, const M *m2, const M *m3);

/*  src must correspond to a square matrix
    and dest size must be n - 1  */
static void remove_row_and_col(const double *src, double *dest, size_t row, size_t col, size_t n);

// assumes size of arr is 9
static double calc_3x3_det(const double *arr);

static double calc_nxn_det(const double *arr, size_t n);
/* --------------- */

/* constructors */
M *__MATRIX_create(size_t num_of_rows, size_t num_of_cols)
{
    if (num_of_cols == 0 || num_of_rows == 0)
        fail_with_msg_line(__FILE__, __LINE__, "Matrix size does not make sense."); 
    M *m = (M*) xmalloc(sizeof(M));
    m->comp = (double*) xmalloc(num_of_rows * num_of_cols * sizeof(double));
    m->rows = num_of_rows;
    m->cols = num_of_cols;
    __MATRIX_setAllComp(m, 0); // initialize to Null MATRIX
    return m;
}

M *__MATRIX_createFromVector(const VECTOR *v)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector."); 
    M *m = __MATRIX_create(__VECTOR_getSize(v), 1);
    for (size_t i = 0; i < m->rows; ++i)
        m->comp[i] = __VECTOR_getComp(v, i);
    return m;
}
/* ------------ */

// destructor
void __MATRIX_destroy(M *m)
{
    if (m != NULL) {
        free(m->comp);
        free(m);
    }
}


/* public methods */
void __MATRIX_copy(const M *from, M *to)
{
    if (from == NULL || to == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    if (from->rows != to->rows || from->cols != to->cols)
        fail_with_msg_line(__FILE__, __LINE__, "Invalid matrix size."); 
    for (size_t i = 0; i < from->rows; ++i)
        for (size_t j = 0; j < from->cols; ++j) {
            size_t index = i * from->cols + j;
            to->comp[index] = from->comp[index];
        }
}

int __MATRIX_export(const M *m, const char *file_name)
{
    if (m == NULL)
        return 0;

    // create export dir if !exists
    static struct stat st = { 0 };
    if (stat(EXPORT_DIR, &st) == -1)
        mkdir(EXPORT_DIR, 0777);
    
    char full_path[MAX_PATH_LEN] = "";
    strcpy(full_path, EXPORT_DIR);
    strncat(full_path, file_name, MAX_PATH_LEN - (strlen(EXPORT_DIR) + 1));

    FILE *f = fopen(full_path, "w");
    if (f == NULL)
        return 0;

    size_t count = fwrite(&(m->rows), sizeof(size_t), 1, f);
    count += fwrite(&(m->cols), sizeof(size_t), 1, f);
    count += fwrite(m->comp, sizeof(double), m->rows * m->cols, f);

    fclose(f);

    if (count != (m->rows * m->cols + 2))
        return 0;
    
    return 1;
}

M *__MATRIX_import(const char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return NULL;

    size_t rows = 0, cols = 0;
    size_t count = fread(&rows, sizeof(size_t), 1, f);
    count += fread(&cols, sizeof(size_t), 1, f);
    M *m = __MATRIX_create(rows, cols);
    count += fread(m->comp, sizeof(double), rows * cols, f);

    fclose(f);

    if (count != (rows * cols + 2)) {
        __MATRIX_destroy(m);
        return NULL;
    }

    return m;
}

bool __MATRIX_isNull(const M *m)
{
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    for (size_t i = 0; i < m->rows; ++i)
        for (size_t j = 0; j < m->cols; ++j)
            if (m->comp[i * m->cols + j] != 0)
                return false;
    return true;
}

size_t __MATRIX_getNumOfRows(const M *m)
{
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    return m->rows;
}

size_t __MATRIX_getNumOfCols(const M *m)
{
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    return m->cols;
}

void __MATRIX_setComp(M *m, size_t row_index, size_t col_index, double new_comp)
{
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    if (row_index >= m->rows || col_index >= m->cols)
        fail_with_msg_line(__FILE__, __LINE__, "Invalid index."); 
    m->comp[row_index * m->cols + col_index] = new_comp;
}

void __MATRIX_setAllComp(M *m, double new_comp)
{
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    size_t n = m->rows * m->cols;
    for (size_t i = 0; i < n; ++i)
        m->comp[i] = new_comp;
}

double __MATRIX_getComp(const M *m, size_t row_index, size_t col_index)
{
    if (row_index >= m->rows || col_index >= m->cols)
        fail_with_msg_line(__FILE__, __LINE__, "Invalid index."); 
    return m->comp[row_index * m->cols + col_index];
}

void __MATRIX_scaleBy(M *m, double scalar)
{
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    for (size_t i = 0; i < m->rows; ++i)
        for (size_t j = 0; j < m->cols; ++j)
            m->comp[i * m->cols + j] *= scalar;
}

void __MATRIX_add(const M *m1, const M *m2, M *result)
{
    if (!are_the_same_size_3(m1, m2, result))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid matrix size."); 
    for (size_t i = 0; i < result->rows; ++i)
        for (size_t j = 0; j < result->cols; ++j) {
            size_t index = i * m1->cols + j;
            result->comp[index] = m1->comp[index] + m2->comp[index];
        }
}

void __MATRIX_subtract(const M *m1, const M *m2, M *result)
{
    if (!are_the_same_size_3(m1, m2, result))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid matrix size."); 
    for (size_t i = 0; i < result->rows; ++i)
        for (size_t j = 0; j < result->cols; ++j) {
            size_t index = i * m1->cols + j;
            result->comp[index] = m1->comp[index] - m2->comp[index];
        }
}

void __MATRIX_multiply(const M *m1, const M *m2, M *result)
{
    if (!(m1->cols == m2->rows && result->rows == m1->rows && result->cols == m2->cols))
        fail_with_msg_line(__FILE__, __LINE__, "Matrix multiplication does not make sense.");
    for (size_t i = 0; i < m1->rows; ++i) {
        for (size_t j = 0; j < m2->cols; ++j) {
            result->comp[i * result->cols + j] = 0;
            for (size_t k = 0; k < m2->rows; ++k)
                result->comp[i * result->cols + j] += m1->comp[i * m1->cols + k] * m2->comp[k * m2->cols + j];
        }
    }
    
}

void __MATRIX_makeIdentityMatrix(M *m)
{
    if (m->rows != m->cols)
        fail_with_msg_line(__FILE__, __LINE__, "Matrix is not square.");
    __MATRIX_setAllComp(m, 0);
    for (size_t i = 0; i < m->rows; ++i)
        m->comp[i * m->cols + i] = 1;
}

double __MATRIX_determinant(const M *m)
{ 
    if (m == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix.");
    return calc_nxn_det(m->comp, m->rows);
}
/* -------------- */


bool are_the_same_size_3(const M *m1, const M *m2, const M *m3)
{
    if (m1 == NULL || m2 == NULL || m3 == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    if (m1->rows == m2->rows && m2->rows == m3->rows)
        if (m1->cols == m2->cols && m2->cols == m3->cols)
            return true;
    return false;
}

void remove_row_and_col(const double *src, double *dest, size_t row, size_t col, size_t n)
{
    if (src == NULL || dest == NULL || row >= n || col >= n)
        fail_with_msg_line(__FILE__, __LINE__, "Invalid argument."); 
    size_t k = 0; // count elements in dest;
    for (size_t i = 0; i < n; ++i) {
        if (i == row)
            continue;
        for (size_t j = 0; j < n; ++j) {
            if (j == col)
                continue;
            dest[k++] = src[i * n + j];
        }
    }
}

double calc_3x3_det(const double *arr)
{
    if (arr == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to matrix."); 
    return (arr[0] * arr[4] * arr[8]) +
           (arr[3] * arr[7] * arr[2]) +
           (arr[6] * arr[1] * arr[5]) -
           (arr[2] * arr[4] * arr[6]) -
           (arr[5] * arr[7] * arr[0]) -
           (arr[8] * arr[1] * arr[3]);
}

double calc_nxn_det(const double *arr, size_t n)
{
    double det = 0;
    switch (n) {
        case 1:
            return arr[0];
        case 2:
            return arr[0] * arr[3] - arr[1] * arr[2];
        case 3:
            calc_3x3_det(arr);
        default:
            for (size_t j = 0; j < n; ++j) {
                double *smaller_arr = (double*) xmalloc((n - 1) * (n - 1) * sizeof(double));
                remove_row_and_col(arr, smaller_arr, 0, j, n);
                det += pow(-1, j) * arr[j] * calc_nxn_det(smaller_arr, n - 1);
                free(smaller_arr);
            }
            return det;
    }
}