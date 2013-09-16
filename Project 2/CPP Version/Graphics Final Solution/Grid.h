#ifndef _GRID_H_
#define _GRID_H_

#include "Stack.h"
#define MAX_INT 5000

class Grid{
    public:
        int rows;
        int cols;

        char** data;
};

class Search{
    public:
        int Length;
        int **Distance;
        int **ParentR;
        int **ParentC;
        Stack *s;
};

Grid* ReadWorld(const char *filename);
Search* FindPath(Grid* g);

#endif

