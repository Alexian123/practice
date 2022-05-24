#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#include <stdbool.h>

#include "linear_algebra_types.h"


/* -------------- METHODS ------------------ */
// constructors
extern MATRIX *__MATRIX_create(size_t num_of_rows, size_t num_of_cols);
extern MATRIX *__MATRIX_createFromVector(const VECTOR *v);

// destructor
extern void __MATRIX_destroy(MATRIX *m);

// deep copy
extern void __MATRIX_copy(const MATRIX *from, MATRIX *to);

// export/import
extern int __MATRIX_export(const MATRIX *m, const char *file_name); // ret 0 on error
extern MATRIX *__MATRIX_import(const char *file_name); // ret NULL on error

// returns false for NULL ptr (refers to the Null MATRIX)
extern bool __MATRIX_isNull(const MATRIX *m);

// returns 0 for NULL ptr
extern size_t __MATRIX_getNumOfRows(const MATRIX *m);
extern size_t __MATRIX_getNumOfCols(const MATRIX *m);

extern void __MATRIX_setComp(MATRIX *m, size_t row_index, size_t col_index, double new_comp);
extern void __MATRIX_setAllComp(MATRIX *m, double new_comp);

// does not check for NULL ptr or out of bounds index
extern double __MATRIX_getComp(const MATRIX *m, size_t row_index, size_t col_index); 

// these operations modify the initial MATRIX
extern void __MATRIX_scaleBy(MATRIX *m, double scalar);

extern void __MATRIX_add(const MATRIX *m1, const MATRIX *m2, MATRIX *result);
extern void __MATRIX_subtract(const MATRIX *m1, const MATRIX *m2, MATRIX *result);
extern void __MATRIX_multiply(const MATRIX *m1, const MATRIX *m2, MATRIX *result);
extern void __MATRIX_makeIdentityMatrix(MATRIX *m);

extern double __MATRIX_determinant(const MATRIX *m);
/* ----------------------------------------- */


// Method namespace (define MATRIX_NAMESPACE before including header)
#ifdef MATRIX_NAMESPACE
static const struct
{
    MATRIX *(*create)(size_t, size_t);
    MATRIX *(*createFromVector)(const VECTOR*);
    void (*destroy)(MATRIX*);
    void (*copy)(const MATRIX*, MATRIX*);
    int (*export)(const MATRIX*, const char*);
    MATRIX *(*import)(const char*);
    bool (*isNull)(const MATRIX*);
    size_t (*getNumOfRows)(const MATRIX*);
    size_t (*getNumOfCols)(const MATRIX*);
    void (*setComp)(MATRIX*, size_t, size_t, double);
    void (*setAllComp)(MATRIX*, double);
    double (*getComp)(const MATRIX*, size_t, size_t);
    void (*scaleBy)(MATRIX*, double);
    void (*add)(const MATRIX*, const MATRIX*, MATRIX*);
    void (*subtract)(const MATRIX*, const MATRIX*, MATRIX*);
    void (*multiply)(const MATRIX*, const MATRIX*, MATRIX*);
    void (*makeIdentityMatrix)(MATRIX*);
    double (*determinant)(const MATRIX*);
} MATRIX_METHODS = { 
    .create = __MATRIX_create,
    .createFromVector = __MATRIX_createFromVector,
    .destroy = __MATRIX_destroy,
    .copy = __MATRIX_copy,
    .export = __MATRIX_export,
    .import = __MATRIX_import,
    .isNull = __MATRIX_isNull,
    .getNumOfRows = __MATRIX_getNumOfRows,
    .getNumOfCols = __MATRIX_getNumOfCols,
    .setComp = __MATRIX_setComp,
    .setAllComp = __MATRIX_setAllComp,
    .getComp = __MATRIX_getComp,
    .scaleBy = __MATRIX_scaleBy,
    .add = __MATRIX_add,
    .subtract = __MATRIX_subtract,
    .multiply = __MATRIX_multiply,
    .makeIdentityMatrix = __MATRIX_makeIdentityMatrix,
    .determinant = __MATRIX_determinant,
};
#endif

#endif