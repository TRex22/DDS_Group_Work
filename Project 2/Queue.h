#ifndef _QUEUE_H_
    #define _QUEUE_H_

#include "LinkList.h"

struct _Queue{
    LinkList *l;
};
typedef struct _Queue Queue;

Queue* queue_init();
void queue_free();

void queue_enqueue(Queue *q, int x, int y);
void queue_dequeue(Queue *q, int *x, int *y);
int queue_size(Queue *q);

#endif
