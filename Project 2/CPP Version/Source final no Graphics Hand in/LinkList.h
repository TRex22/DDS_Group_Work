#ifndef _LINKLIST_H_
    #define _LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>

class Link{
    public:
        int x;
        int y;
        Link *next;
};

class LinkList{
    public:
        int mysize;
        Link *head;
        Link *tail;

    public:
        LinkList();
        ~LinkList();
        void addFront(int x, int y);
        void addBack(int x, int y);
        void getFront(int &x, int &y);
        int  size();
        void print();
};
#endif
