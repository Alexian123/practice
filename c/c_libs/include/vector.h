#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>
#include <stdbool.h>

#include "linear_algebra_types.h"


/* -------------- METHODS ------------------ */
// constructors
extern VECTOR *__VECTOR_create(size_t size);
extern VECTOR *__VECTOR_createFromColOfMatrix(const MATRIX *m, size_t col);
extern VECTOR *__VECTOR_createFromRowOfMatrix(const MATRIX *m, size_t row);

// destructor
extern void __VECTOR_destroy(VECTOR *v);

// deep copy
extern void __VECTOR_copy(const VECTOR *from, VECTOR *to);

// export/import
extern int __VECTOR_export(const VECTOR *v, const char *file_name); // ret 0 on error
extern VECTOR *__VECTOR_import(const char *file_name); // ret NULL on error

extern bool __VECTOR_isNull(const VECTOR *v);
extern size_t __VECTOR_getSize(const VECTOR *v);
extern void __VECTOR_setComp(VECTOR *v, size_t index, double new_comp);
extern void __VECTOR_setAllComp(VECTOR *v, double new_comp);
extern double __VECTOR_getComp(const VECTOR *v, size_t index); 

// these operations modify the initial vectors
extern void __VECTOR_scaleBy(VECTOR *v, double scalar);
extern void __VECTOR_normalize(VECTOR *v);
extern void __VECTOR_applyTransformation(VECTOR **v, const MATRIX *m);

extern void __VECTOR_add(const VECTOR *v1, const VECTOR *v2, VECTOR *result);
extern void __VECTOR_subtract(const VECTOR *v1, const VECTOR *v2, VECTOR *result);
extern double __VECTOR_stdDotProduct(const VECTOR *v1, const VECTOR *v2);
extern void __VECTOR_project(const VECTOR *v1, const VECTOR *v2, VECTOR *result);
extern double __VECTOR_getNorm(const VECTOR *v);
extern double __VECTOR_getCosine(const VECTOR *v1, const VECTOR *v2);
extern bool __VECTOR_areOrthogonal(const VECTOR *v1, const VECTOR *v2);
/* ----------------------------------------- */

// Method namespace (define VECTOR_NAMESPACE before including header)
#ifdef VECTOR_NAMESPACE
static const struct
{
    VECTOR *(*create)(size_t);
    VECTOR *(*createFromColOfMatrix)(const MATRIX*, size_t);
    VECTOR *(*createFromRowOfMatrix)(const MATRIX*, size_t);
    void (*destroy)(VECTOR*);
    void (*copy)(const VECTOR*, VECTOR*);
    int (*export)(const VECTOR*, const char*);
    VECTOR *(*import)(const char*);
    bool (*isNull)(const VECTOR*);
    size_t (*getSize)(const VECTOR*);
    void (*setComp)(VECTOR*, size_t, double);
    void (*setAllComp)(VECTOR*, double);
    double (*getComp)(const VECTOR*, size_t);
    void (*scaleBy)(VECTOR*, double);
    void (*normalize)(VECTOR*);
    void (*applyTransformation)(VECTOR**, const MATRIX*);
    void (*add)(const VECTOR*, const VECTOR*, VECTOR*);
    void (*subtract)(const VECTOR*, const VECTOR*, VECTOR*);
    double (*stdDotProduct)(const VECTOR*, const VECTOR*);
    void (*project)(const VECTOR*, const VECTOR*, VECTOR*);
    double (*getNorm)(const VECTOR*);
    double (*getCosine)(const VECTOR*, const VECTOR*);
    bool (*areOrthogonal)(const VECTOR*, const VECTOR*);
} VECTOR_METHODS = { 
    .create = __VECTOR_create,
    .createFromColOfMatrix = __VECTOR_createFromColOfMatrix,
    .createFromRowOfMatrix = __VECTOR_createFromRowOfMatrix,
    .destroy = __VECTOR_destroy,
    .copy = __VECTOR_copy,
    .export = __VECTOR_export,
    .import = __VECTOR_import,
    .isNull = __VECTOR_isNull,
    .getSize = __VECTOR_getSize,
    .setComp = __VECTOR_setComp,
    .setAllComp = __VECTOR_setAllComp,
    .getComp = __VECTOR_getComp,
    .scaleBy = __VECTOR_scaleBy,
    .normalize = __VECTOR_normalize,
    .applyTransformation = __VECTOR_applyTransformation,
    .add = __VECTOR_add,
    .subtract = __VECTOR_subtract,
    .stdDotProduct = __VECTOR_stdDotProduct,
    .project = __VECTOR_project,
    .getNorm = __VECTOR_getNorm,
    .getCosine = __VECTOR_getCosine,
    .areOrthogonal = __VECTOR_areOrthogonal,
};
#endif

#endif