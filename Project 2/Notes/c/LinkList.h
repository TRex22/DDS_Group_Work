#ifndef _LINKLIST_H_
    #define _LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>

struct _Link{
    int x;
    int y;
    struct _Link *next;
};
typedef struct _Link Link;

struct _LinkList{
    int size;
    Link *head;
    Link *tail;
};
typedef struct _LinkList LinkList;

LinkList* ll_init();
void ll_free(LinkList *l);

void ll_addFront(LinkList *l, int x, int y);
void ll_addBack(LinkList *l, int x, int y);
void ll_getFront(LinkList *l, int *x, int *y);
int  ll_size(LinkList *l);
void ll_print(LinkList *l);

#endif
