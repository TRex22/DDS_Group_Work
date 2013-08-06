#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "postfix.h"

int counter;

void assert(int i, int v, char* msg){
    if(i == v)
        printf("%2d - Correct - %s\n", counter, msg);
    else
        printf("%2d - Wrong  - %s \t - %d not %d\n", counter, msg, i, v);
    counter++;
}
void assert(char i, char v, char* msg){
    if(i == v)
        printf("%2d - Correct - %s\n", counter, msg);
    else
        printf("%2d - Wrong   - %s \t - %c not %c\n", counter, msg, i, v);
    counter++;
}

void assert(char* i, char* v, char* msg){
    int idx = 0, comp;
    while(i[idx] != '\0' && v[idx] != '\0'){
        comp = (i[idx] == v[idx]);
        if(!comp) break;
        idx++;
    }
    if(comp)
        printf("%2d - Correct - %s\n", counter, msg, i, v);
    else
        printf("%2d - Wrong   - %s \t - %s not %s\n", counter, msg, i, v);
    counter++;
}

void Test_CharStack(){
    printf("Testing Character Stacks................................\n");
    // Testing the character stack
    CharStack *cStack;
    int n;
    cStack = stack_c_init();

    n = cStack->size;

    stack_c_push(cStack, 'h'); n++;
    stack_c_push(cStack, 'e'); n++;
    stack_c_push(cStack, 'l'); n++;
    stack_c_push(cStack, 'l'); n++;
    stack_c_push(cStack, 'o'); n++;
    assert(cStack->size, n, "stack_c_push - size");
    assert(cStack->data[0], 'h', "stack_c_push - value");
    assert(cStack->data[1], 'e', "stack_c_push - value");
    assert(cStack->data[2], 'l', "stack_c_push - value");
    assert(cStack->data[3], 'l', "stack_c_push - value");
    assert(cStack->data[4], 'o', "stack_c_push - value");

    assert(stack_c_pop(cStack), 'o', "stack_c_pop - value"); n--;
    assert(cStack->size, n, "stack_c_pop - size");
    assert(stack_c_pop(cStack), 'l', "stack_c_pop - value"); n--;
    assert(cStack->size, n, "stack_c_pop - size");
    assert(stack_c_pop(cStack), 'l', "stack_c_pop - value"); n--;
    assert(cStack->size, n, "stack_c_pop - size");
    assert(stack_c_pop(cStack), 'e', "stack_c_pop - value"); n--;
    assert(cStack->size, n, "stack_c_pop - size");

    assert(stack_c_peek(cStack), 'h', "stack_c_peek - value");
    assert(cStack->size, n, "stack_c_peek - size");
}

void Test_IntStack(){
    printf("Testing Integer Stacks................................\n");
    // Testing the integer stack
    IntStack *iStack;
    int n;

    iStack = stack_i_init();
    n = iStack->size;

    stack_i_push(iStack, 1); n++;
    stack_i_push(iStack, 2); n++;
    stack_i_push(iStack, 3); n++;
    stack_i_push(iStack, 4); n++;
    assert(iStack->size, n, "stack_i_push - size");
    assert(iStack->data[0], 1, "stack_i_push - value");
    assert(iStack->data[1], 2, "stack_i_push - value");
    assert(iStack->data[2], 3, "stack_i_push - value");
    assert(iStack->data[3], 4, "stack_i_push - value");

    assert(stack_i_pop(iStack), 4, "stack_i_pop - value"); n--;
    assert(iStack->size, n, "stack_i_pop - size");
    assert(stack_i_pop(iStack), 3, "stack_i_pop - value"); n--;
    assert(iStack->size, n, "stack_i_pop - size");
    assert(stack_i_pop(iStack), 2, "stack_i_pop - value"); n--;
    assert(iStack->size, n, "stack_i_pop - size");

    assert(stack_i_peek(iStack), 1, "stack_i_peek - value");
    assert(iStack->size, n, "stack_i_peek - size");
}

void Test_Calculate(){
    printf("Testing Calculate......................................\n");
    int a;
    // 5*(3+1) = 20
    assert(calculate("531+*"), 20, "calculate, valid - 5321+*");
    // 5 * 3 + 1 = 16
    assert(calculate("53*1+"), 16, "calculate, valid - 53*1+");
    // (9/3) - (1+1) = 1
    assert(calculate("93/11+-"), 1, "calculate, valid - 93/11+-");
    
    assert(calculate("531++*"), -2000, "calculate, invalid - 531++*");
    assert(calculate("531+"), -1000, "calculate, invalid - 531+");
}

void Test_Convert(){
    printf("Testing Convert......................................\n");
    int a;
    // 5*(3+1) = 20
    assert(convert("5*(3+1)"), "531+*", "convert - 5321+*");
    // 5 * 3 + 1 = 16
    assert(convert("5*3+1"), "53*1+", "convert - 53*1+");
    // (9/3) - (1+1) = 1
    assert(convert("9/3-(1+1)"), "93/11+-", "convert - 93/11+-");

}

void Test_Calculate_Extra(){
    printf("Testing Calculate Extra Credit.........................\n");
    int a;
    // 5*(3+1) = 20
    assert(calculate_extra("50 3 1 + *"), 200, "calculate, valid - 50 3 1 + *");
    // 5 * 3 + 1 = 16
    assert(calculate_extra("5 3 * 10 +"), 25, "calculate, valid - 5 3 * 10 +");
    // (9/3) - (1+1) = -1
    assert(calculate_extra("96 3 / 10 1 + -"), 21, "calculate, valid - 96 3 / 10 1 + - ");
    
    assert(calculate_extra("50 3 10 + + *"), -2000, "calculate, invalid - 50 3 10 + + *");
    assert(calculate_extra("5 23 11 +"), -1000, "calculate, invalid - 5 23 11+");
}

int main(){
    Test_CharStack();
    Test_IntStack();

    Test_Calculate();
    Test_Convert();

    Test_Calculate_Extra();
}
