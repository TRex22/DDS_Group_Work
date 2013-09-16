#include <stdio.h>
#include <stdlib.h>

#include "LinkList.h"

LinkList::LinkList(){
    mysize = 0;
    head = NULL;
    tail = NULL;
}

LinkList::~LinkList(){
    int x, y;
    while(mysize > 0){
        getFront(x, y);
    }
}

void LinkList::addFront(int x, int y){
    Link *temp = new Link();

    temp->x = x;
    temp->y = y;
    temp->next = head;
    head = temp;

    if(mysize == 0)
        tail = temp;

    mysize++;
}

void LinkList::addBack(int x, int y){
    Link *temp = new Link();

    temp->x = x;
    temp->y = y;
    temp->next = NULL;

    if(mysize > 0)
        tail->next = temp;
    tail = temp;

    if(mysize == 0)
        head = temp;

    mysize++;
}

void LinkList::getFront(int &x, int &y){
    Link *temp; 

    if(mysize <= 0){
        printf("Tried to get value from empty linked list.");
        exit(1);
    }

    temp = head;

    x = temp->x;
    y = temp->y;

    head = temp->next;
    delete temp;

    mysize--;
}

int LinkList::size(){
    return mysize;
}

void LinkList::print(){
    Link* temp = head;
    printf("[ ");
    while(temp){
        printf("(%d,%d) ", temp->x, temp->y);
        temp = temp->next;
    }
    printf("]\n");
}
