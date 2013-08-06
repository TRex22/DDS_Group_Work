#ifndef _POSTFIX_H
    #define _POSTFIX_H

#define DEFAULT_SIZE 255
/*********************************************************/
// Stack Containing Characters
struct _cStack {
    int size;
    int capacity;
    char* data;
};
typedef struct _cStack CharStack;

// Allocate the stack and setup size and capacity
CharStack* stack_c_init();
// Push to the top of stack
void stack_c_push(CharStack*, char);
// Pop off the top of stack
char stack_c_pop(CharStack*);
// Return the top of the stack without removing it
char stack_c_peek(CharStack*);

/*********************************************************/
// Stack Contining Integers
struct _iStack {
    int size;
    int capacity;
    int* data;
};
typedef struct _iStack IntStack;

// Allocate the stack and setup size and capacity
IntStack* stack_i_init();
// Push to the top of stack
void stack_i_push(IntStack*, int);
// Pop from the top of stack
int  stack_i_pop(IntStack*);
// Return the top of the stack without removing it
int  stack_i_peek(IntStack*);

/*********************************************************/
int calculate(char*);
char* convert(char*);

int calculate_extra(char*);

#endif
