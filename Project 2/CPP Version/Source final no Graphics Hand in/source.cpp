#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <cstdio>

#include "Grid.h"

#include "LinkList.h"
#include "Stack.h"
#include "Queue.h"


/* ------------- QUEUE FUNCTIONS ------------------ */
Queue::Queue(){
	//Queue *q=(Queue*)malloc(sizeof(Queue));
	//q->l=new LinkList();
	//l=new LinkList();
	//size =0;
	//return q;
	//printf("hello");
	l = new LinkList();
	//l->mysize=0;
}
Queue::~Queue(){
    if(l != NULL)
        delete l;
}

void Queue::enqueue(int x, int y){
	l->addBack(x, y);
	//size++;
}

void Queue::dequeue(int &x, int &y){
	if (l->head== NULL)
	{
		//return;
		//kill bot
	}
	else
	{
		l->getFront(x, y);
	}
	
}

int Queue::size(){
	return l->size();
}

/* ------------- STACK FUNCTIONS ------------------ */
Stack::Stack(){
	//size = 0;
	//printf("hello");
	//Stack *s = (Stack*)malloc(sizeof(Stack));
	//s->l = new LinkList();
	
	//mysize auto set to 0
	l = new LinkList();
	
	//l->mysize=0;
	//l = new LinkList();
	//s->l->mysize = 0;
	//mysize = 0;
	//s->l->mysize=0;
	//printf("size %d\n", size());
	//return s;
}

Stack::~Stack(){
    if(l != NULL)
        delete l;
}

void Stack::push(int x, int y){
	l->addFront(x, y);
}

void Stack::pop(int &x, int &y){
	if (l->head== NULL)
	{
		//return;
		//kill bot
	}
	else
	{
		l->getFront(x, y);
	}
}

int Stack::size(){
	//printf("booby");
	return l->size();
}

/* ------------- SEARCH FUNCTIONS ------------------ */
Grid* ReadWorld(const char* filename){
	FILE *filey = fopen(filename, "r+");
	if (filey == NULL)
	{
		//printf("Error Opening File\n");	
		//just ignore for now not really important for this
	}	
	
	int i,j; //counters
	Grid *theGrid = new Grid;
	//printf("Vars\n");
	fscanf(filey, "%d %d\n", &theGrid->rows, &theGrid->cols);
	//printf("Read file\n");
	theGrid -> data = new char*[theGrid->rows];
	//printf("The Grid malloc\n");
	//printf("Size of The Grid: %d\n", (sizeof(theGrid)));
	//j = theGrid->rows;
	//printf("J: %d\n", j);
	
	for(i=0;i<theGrid->rows;i++)
	{
		theGrid->data[i] = new char[theGrid->cols+3];
		//printf("%s",theGrid->data[i]);
		//printf("Data at i: %s Loop i: %d \n",theGrid->data[i], i);
	}
	
	for (i=0;i<theGrid->rows;i++)
	{
		fgets(theGrid->data[i], theGrid->cols+3, filey);
	}

	fclose(filey);
	//printf("End.\n");
	return theGrid;
}

Search* FindPath(Grid* g){
	Queue *q = new Queue();
	//printf("1\n");
	Search* se = new Search;
	//printf("2\n");
	se->s=new Stack();
	//printf("3\n");
	se->Length=0;
	//printf("4\n");
	int i=0, j=0, rows = g->rows, cols = g->cols;
	
	se->ParentR = new int*[rows];
	se->ParentC = new int*[rows];
	se->Distance= new int*[rows];
	//printf("5\n");
	
	//printf("Here\n");
	//printf("Rows %d\n", rows);
	//printf("i: %d",i);
	
	//system.end(0);
	
	i=0, j=0;
	int startR, startC, goalR, goalC;
	for(i=0;i<rows;i++)
	{
		se->ParentR[i] = new int[cols];
		se->ParentC[i] = new int[cols];
		se->Distance[i]= new int[cols];

		for(j=0;j<cols;j++)
		{	
			se->ParentR[i][j] = -2;
			se->ParentC[i][j] = -2;
			
			se->Distance[i][j] = MAX_INT;
			
			if(g->data[i][j] == 'S')
			{
				startR=i;
				startC=j;
			}else if(g->data[i][j] == 'G'){
				goalR = i;
				goalC = j;
				g->data[i][j] = ' ';
			}

		}
	}
	
	se->Distance[startR][startC]=0;
	se->ParentR[startR][startC]=-1;
	se->ParentC[startR][startC]=-1;

	q->enqueue(startR, startC);
	int currR, currC;
			//printf("hello\n");
	currR = startR;
	currC = startC;
	//printf("Rows: %d Cols: %d\n",rows,cols);
	//printf("queue size: %d\n",q->size());
			//printf("hello\n");
	while((q->size())!=0 && !(currR == goalR && currC == goalC))
	{

		//printf("Rows: %d Cols: %d\n",rows,cols);
		q->dequeue(currR, currC);
		
		//up
		if(g->data[currR-1][currC]==' ' && se->ParentR[currR-1][currC]==-2 && se->ParentC[currR-1][currC]==-2)
		{
			se->Distance[currR-1][currC] = se->Distance[currR][currC] + 1;
			se->ParentR[currR-1][currC] = currR;
			se->ParentC[currR-1][currC] = currC;
			q->enqueue(currR-1, currC);
		}
		
		//down
		if(g->data[currR+1][currC]==' ' && se->ParentR[currR+1][currC]==-2 && se->ParentC[currR+1][currC]==-2)
		{
			se->Distance[currR+1][currC] = se->Distance[currR][currC] + 1;
			se->ParentR[currR+1][currC] = currR;
			se->ParentC[currR+1][currC] = currC;
			q->enqueue(currR+1, currC);
		}
		
		//left
		if(g->data[currR][currC-1]==' ' && se->ParentR[currR][currC-1]==-2 && se->ParentC[currR][currC-1]==-2)
		{
			se->Distance[currR][currC-1] = se->Distance[currR][currC] + 1;
			se->ParentR[currR][currC-1] = currR;
			se->ParentC[currR][currC-1] = currC;
			q->enqueue(currR, currC-1);
		}
		
		//right
		if(g->data[currR][currC+1]==' ' && se->ParentR[currR][currC+1]==-2 && se->ParentC[currR][currC+1]==-2)
		{
			se->Distance[currR][currC+1] = se->Distance[currR][currC] + 1;
			se->ParentR[currR][currC+1] = currR;
			se->ParentC[currR][currC+1] = currC;
			q->enqueue(currR, currC+1);
		}
	}
	
	if(q->size()==0 && g->data[currR][currC]!='G')
	{
		se->Length=-1;
		return se;
	}
	else
	{
		se->Length=se->Distance[currR][currC];
		se->s->push(currR, currC);
		//se->s->
		while(currR != -1 && currC != -1)
		{
			se->s->push(se->ParentR[currR][currC], se->ParentC[currR][currC]);
			int tempR = currR, tempC=currC;
			currR=se->ParentR[tempR][tempC];
			currC=se->ParentC[tempR][tempC];	
		}		
		se->s->pop(currR, currC);
		return se;
	}
}

/* --------------MISC FUNCTIONS--------------------- */
//these are fuctions I have used in FAC and DDS projects
//which I have found useful
int PowerFn (int no, int power)
{
	int j, ans;
	if (power == 0)
	{
		ans = 1;
	}
	else if (power == 1)
	{
		ans = no;
	}
	else
	{
		ans = no;
		for (j = 1; j < power; j++)
		{
			ans = ans*no;
		}
	}
	return ans;
}


