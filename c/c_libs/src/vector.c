#include "vector.h"
#include "matrix.h"
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
typedef struct __Vec
{
    double *comp;
    size_t size;
} V;


/* private methods */
static bool are_the_same_size_3(const V *v1, const V *v2, const V *v3);
/* --------------- */

/* constructor */
V *__VECTOR_create(size_t size)
{
    if (size == 0)
        fail_with_msg_line(__FILE__, __LINE__, "Vector of size 0 does not make sense.");
    V *v = (V*) xmalloc(sizeof(V));
    v->comp = (double*) xmalloc(size * sizeof(double));
    v->size = size;
    __VECTOR_setAllComp(v, 0); // initialize to null vector
    return v;
}

V *__VECTOR_createFromColOfMatrix(const MATRIX *m, size_t col)
{
    if (m == NULL || col >= __MATRIX_getNumOfCols(m))
        fail_with_msg("Error creating vector from column matrix.");
    V *v = __VECTOR_create(__MATRIX_getNumOfRows(m));
    for (size_t i = 0; i < v->size; ++i)
        v->comp[i] = __MATRIX_getComp(m, i, col);
    return v;
}

V *__VECTOR_createFromRowOfMatrix(const MATRIX *m, size_t row)
{
    if (m == NULL || row >= __MATRIX_getNumOfRows(m))
        fail_with_msg("Error creating vector from row matrix.");
    V *v = __VECTOR_create(__MATRIX_getNumOfCols(m));
    for (size_t j = 0; j < v->size; ++j)
        v->comp[j] = __MATRIX_getComp(m, row, j);
    return v;
}
/* ----------- */

// destructor
void __VECTOR_destroy(V *v)
{
    if (v != NULL) {
        free(v->comp);
        free(v);
    }
}


/* public methods */
void __VECTOR_copy(const V *from, V *to)
{
    if (from == NULL || to == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    if (from->size == to->size)
        for (size_t i = 0; i < from->size; ++i)
            to->comp[i] = from->comp[i];
}

int __VECTOR_export(const V *v, const char *file_name)
{
    if (v == NULL)
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

    size_t count = fwrite(&(v->size), sizeof(size_t), 1, f);
    count += fwrite(v->comp, sizeof(double), v->size, f);

    fclose(f);

    if (count != (v->size + 1))
        return 0;
    
    return 1;
}

V *__VECTOR_import(const char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return NULL;

    size_t size = 0;
    size_t count = fread(&size, sizeof(size_t), 1, f);
    V *v = __VECTOR_create(size);
    count += fread(v->comp, sizeof(double), size, f);

    fclose(f);

    if (count != (size + 1)) {
        __VECTOR_destroy(v);
        return NULL;
    }

    return v;
}

bool __VECTOR_isNull(const V *v)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    for (size_t i = 0; i < v->size; ++i)
        if (v->comp[i] != 0)
            return false;
    return true;
}

size_t __VECTOR_getSize(const V *v)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    return v->size;
}

void __VECTOR_setComp(V *v, size_t index, double new_comp)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    if (index >= v->size)
        fail_with_msg_line(__FILE__, __LINE__, "Invalid index.");
    v->comp[index] = new_comp;
}

void __VECTOR_setAllComp(V *v, double new_comp)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    for (size_t i = 0; i < v->size; ++i)
        v->comp[i] = new_comp;
}

double __VECTOR_getComp(const V *v, size_t index)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    if (index >= v->size)
        fail_with_msg_line(__FILE__, __LINE__, "Invalid index.");
    return v->comp[index];
}

void __VECTOR_scaleBy(V *v, double scalar)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    for (size_t i = 0; i < v->size; ++i)
        v->comp[i] *= scalar;
}

void __VECTOR_normalize(V *v)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    double norm = __VECTOR_getNorm(v);
    if (norm == 0 || norm == 1) // the Null vector or alerady normalized
        return;
    for (size_t i = 0; i < v->size; ++i)
        v->comp[i] /= norm;
}

void __VECTOR_applyTransformation(V **v, const MATRIX *m)
{
    if (v == NULL || (*v) == NULL || m == NULL || (__MATRIX_getNumOfCols(m) != (*v)->size))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid argument.");
    
    // copy v to a 1 col matrix
    MATRIX *aux = __MATRIX_createFromVector(*v);

    // get the result of the multiplaction
    MATRIX *result = __MATRIX_create(__MATRIX_getNumOfRows(m), 1);
    __MATRIX_multiply(m, aux, result);

    // delete the old v and copy the result
    __VECTOR_destroy(*v);
    *v = __VECTOR_createFromColOfMatrix(result, 0);

    // cleanup
    __MATRIX_destroy(aux);
    __MATRIX_destroy(result);
}

void __VECTOR_add(const V *v1, const V *v2, V *result)
{
    if (!are_the_same_size_3(v1, v2, result))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid vector size.");
    for (size_t i = 0; i < result->size; ++i)
        result->comp[i] = v1->comp[i] + v2->comp[i];
}

void __VECTOR_subtract(const V *v1, const V *v2, V *result)
{
    if (!are_the_same_size_3(v1, v2, result))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid vector size.");
    for (size_t i = 0; i < result->size; ++i)
        result->comp[i] = v1->comp[i] - v2->comp[i];
}

double __VECTOR_stdDotProduct(const V *v1, const V *v2)
{
    if (v1 == NULL || v2 == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    double result = 0;
    for (size_t i = 0; i < v1->size; ++i)
        result += (v1->comp[i] * v2->comp[i]);
    return result;
}

void __VECTOR_project(const V *v1, const V *v2, V *result)
{
    if (!are_the_same_size_3(v1, v2, result))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid vector size.");
    __VECTOR_copy(v2, result);
    __VECTOR_scaleBy(result, __VECTOR_stdDotProduct(v1, v2) / __VECTOR_stdDotProduct(v2, v2));
}

double __VECTOR_getNorm(const V *v)
{
    if (v == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    return sqrt(__VECTOR_stdDotProduct(v, v));
}

double __VECTOR_getCosine(const V *v1, const V *v2)
{
    if (v1 == NULL || v2 == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector.");
    return __VECTOR_stdDotProduct(v1, v2) / (__VECTOR_getNorm(v1) * __VECTOR_getNorm(v2));
}

bool __VECTOR_areOrthogonal(const V *v1, const V *v2)
{
    if (v1 == NULL || v2 == NULL || (v1->size != v2->size))
        fail_with_msg_line(__FILE__, __LINE__, "Invalid argument.");
    if (__VECTOR_isNull(v1) || __VECTOR_isNull(v2))
        return false;
    return (__VECTOR_stdDotProduct(v1, v2) == 0);
}
/* -------------- */

bool are_the_same_size_3(const V *v1, const V *v2, const V *v3)
{
    if (v1 == NULL || v2 == NULL || v3 == NULL)
        fail_with_msg_line(__FILE__, __LINE__, "Null pointer to vector."); 
    if (v1->size == v2->size && v2->size == v3->size)
        return true;
    return false;
}