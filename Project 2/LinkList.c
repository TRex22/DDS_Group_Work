#include <stdio.h>
#include <stdlib.h>

#include "LinkList.h"

LinkList* ll_init(){
    LinkList *out = (LinkList*) malloc(sizeof(LinkList));

    out->size = 0;
    out->head = NULL;
    out->tail = NULL;

    return out; 
}

void ll_free(LinkList *l){
    int x, y;
    while(ll_size(l)){
        ll_getFront(l, &x, &y);
    }
    free(l);
}


void ll_addFront(LinkList *l, int x, int y){
    Link *temp = (Link*) malloc(sizeof(Link));

    temp->x = x;
    temp->y = y;
    temp->next = l->head;
    l->head = temp;

    if(l->size == 0)
        l->tail = temp;

    l->size++;
}

void ll_addBack(LinkList *l, int x, int y){
    Link *temp = (Link*) malloc(sizeof(Link));

    temp->x = x;
    temp->y = y;
    temp->next = NULL;

    if(l->size > 0)
        l->tail->next = temp;
    l->tail = temp;

    if(l->size == 0)
        l->head = temp;

    l->size++;
}

void ll_getFront(LinkList *l, int *x, int *y){
    Link *temp; 

    if(ll_size(l) <= 0){
        error("Tried to get value from empty linked list.");
    }

    temp = l->head;

    *x = temp->x;
    *y = temp->y;

    l->head = temp->next;
    free(temp);

    l->size--;
}

int ll_size(LinkList *l){
    return l->size;
}

void ll_print(LinkList *l){
    Link* temp = l->head;
    printf("[ ");
    while(temp){
        printf("(%d,%d) ", temp->x, temp->y);
        temp = temp->next;
    }
    printf("]\n");
}
