#ifndef _GRID_H_
#define _GRID_H_

#include "Stack.h"
#define MAX_INT 5000

struct _Grid{
    int rows;
    int cols;

    char** data;
};
typedef struct _Grid Grid;

struct _Search{
    int Length;
    int **Distance;
    int **ParentR;
    int **ParentC;
    Stack *s;
};
typedef struct _Search Search;

Grid* ReadWorld(const char *filename);
Search* FindPath(Grid* g);

#endif

