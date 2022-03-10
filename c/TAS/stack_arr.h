#ifndef __STACK_ARR_H__
#define __STACK_ARR_H__

#include <stddef.h>

//#define __DEBUG_STACK_ARR

#define POP_ERROR 0

typedef int stack_element;
typedef struct _StackArr Stack;

// constructor & destructor
Stack *createStack(size_t capacity);
void destroyStack(Stack *target);

// basic operations
void push(Stack *target, stack_element elem);
stack_element pop(Stack *target);
size_t getStackSize(const Stack *target);

#endif