#ifndef _STACK_H_
    #define _STACK_H_

#include "LinkList.h"

struct _Stack{
    LinkList *l;
};
typedef struct _Stack Stack;

Stack* stack_init();
void stack_free();

void stack_pop(Stack *s, int *x, int *y);
void stack_push(Stack *s, int x, int y);
int stack_size(Stack *s);

#endif
