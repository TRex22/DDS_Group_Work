#ifndef _STACK_H_
    #define _STACK_H_

#include "LinkList.h"

class Stack{
    public:
        LinkList *l;

    public:
        Stack();
        ~Stack();

        void pop(int &x, int &y);
        void push(int x, int y);
        int size();
};

#endif
