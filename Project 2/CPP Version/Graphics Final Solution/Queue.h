#ifndef _QUEUE_H_
    #define _QUEUE_H_

#include "LinkList.h"

class Queue{
    public:
        LinkList *l;
    public:
        Queue();
        ~Queue();

        void enqueue(int x, int y);
        void dequeue(int &x, int &y);
        int size();
};
#endif
