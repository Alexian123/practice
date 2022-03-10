#include "stack_arr.h"

#include <stdlib.h>

#ifdef __DEBUG_STACK_ARR
#include <stdio.h>
#endif

static const size_t RESIZE_FACTOR = 5;

typedef struct _StackArr
{
    stack_element *arr;
    size_t size;
    size_t capacity;
} ST;

void resize_arr(ST *s, size_t new_size) {
    stack_element *arr = realloc(s->arr, new_size * sizeof(stack_element));
    if (arr) {
#ifdef __DEBUG_STACK_ARR
        printf("\n[DEBUG]Resizing stack. Old: %lu. New: %lu.\n", s->capacity, new_size);
#endif
        s->capacity = new_size;
        s->arr = arr;
    }
}

// constructor & destructor
ST *createStack(size_t capacity) {
    if (capacity < 1)
        return NULL;
    ST *s = malloc(sizeof(ST));
    if (!s)
        return NULL;
    if (!(s->arr = malloc(capacity * sizeof(stack_element))))
        return NULL;
    s->size = 0; 
    s->capacity = capacity;
    return s;
}

void destroyStack(ST *target) {
    free(target->arr);
    free(target);
}


// basic operations
void push(ST *target, stack_element elem) {
    if (target->size == target->capacity)
        resize_arr(target, target->capacity + RESIZE_FACTOR);
    target->arr[(target->size)++] = elem;
}

stack_element pop(ST *target) {
    if (target->size == 0)
        return POP_ERROR;
    stack_element el = target->arr[target->size - 1];
    --(target->size);
    if (target->capacity - target->size >= RESIZE_FACTOR*2)
        resize_arr(target, target->capacity - RESIZE_FACTOR*2);
    return el;
}

size_t getStackSize(const ST *target) {
    return target->size;
}