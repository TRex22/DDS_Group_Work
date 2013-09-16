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
	return l->mysize;
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
	return l->mysize;
}

/* ------------- SEARCH FUNCTIONS ------------------ */
Grid* ReadWorld(const char* filename){
	FILE *filey = fopen(filename, "r");
	if (filey == NULL)
	{
		//printf("Error Opening File\n");	
		//just ignore for now not really important for this
	}	
	
	int i,j; //counters
	Grid *theGrid = (Grid*)malloc(sizeof(Grid));
	//printf("Vars\n");
	fscanf(filey, "%d %d\n", &theGrid->rows, &theGrid->cols);
	//printf("Read file\n");
	theGrid -> data = (char**)malloc(sizeof(char*)*theGrid->rows);
	//printf("The Grid malloc\n");
	//printf("Size of The Grid: %d\n", (sizeof(theGrid)));
	j = theGrid->rows;
	//printf("J: %d\n", j);
	
	for(i=0;i<j;i++)
	{
		theGrid->data[i] = (char*)malloc(sizeof(char)*theGrid->cols);
		fgets(theGrid->data[i], theGrid->cols+2, filey);
		//printf("Data at i: %s Loop i: %d \n",theGrid->data[i], i);
	}

	fclose(filey);
	//printf("End.\n");
	return theGrid;
}

Search* FindPath(Grid* g){
	Queue *q = new Queue();
	//printf("1\n");
	Search* se=(Search*)malloc(sizeof(Search));
	//printf("2\n");
	se->s=new Stack();
	//printf("3\n");
	se->Length=0;
	//printf("4\n");
	
	se->ParentR=(int**)malloc(sizeof(int*));
	//printf("5\n");
	int i=0, j=0, rows = g->rows, cols = g->cols;
	//printf("Here\n");
	//printf("Rows %d\n", rows);
	//printf("i: %d",i);
	for(i=0;i<rows;i++)
	{
		//printf("Rows %d\n", rows);
		
		//system("sleep(1000)");
		//printf("%d\n",i);
		se->ParentR[i]=(int*)malloc(sizeof(int));
		//printf("6\n");
		//cant access i=1...n
	}
	//printf("Here\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{	
			//printf ("test i: %d j: %d\n",i,j);
			//se->ParentR[1][1]=-2;
			se->ParentR[i][j]=-2;
		}
	}
	//printf("working here...");
	se->ParentC=(int**)malloc(sizeof(int*));
	//printf("7\n");
	for(i=0;i<rows;i++)
	{
		se->ParentC[i]=(int*)malloc(sizeof(int));
		//printf("8\n");
	}
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			//printf("%d\n",i);
			se->ParentC[i][j]=-2;
		}
	}

	se->Distance=(int**)malloc(sizeof(int*));
	//printf("9\n");
	for(i=0;i<rows;i++)
	{
		se->Distance[i]=(int*)malloc(sizeof(int));
		//printf("10\n");
		for(j=0;j<cols;j++)
		{
			se->Distance[i][j]=MAX_INT;
		}
	}
	
	i=0, j=0;
	int *startR, *startC;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			if(g->data[i][j]=='S')
			{
				*startR=i;
				*startC=j;
				break;
			}
		}
	}
	
	se->Distance[*startR][*startC]=0;
	se->ParentR[*startR][*startC]=-1;
	se->ParentC[*startR][*startC]=-1;
	
	//*q = enqueue(*startR, *startC);
	q->enqueue(*startR, *startC);
	
	int *currR, *currC;
	while(q->size()!=0 && g->data[*currR][*currC]!='G')
	{
		q->enqueue(*currR, *currC);
		
		//up
		if(g->data[*currR-1][*currC]==' ' && se->ParentR[*currR-1][*currC]==-2 && se->ParentC[*currR-1][*currC]==-2)
		{
			se->Distance[*currR-1][*currC] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR-1][*currC] = *currR;
			se->ParentC[*currR-1][*currC] = *currC;
			q->enqueue(*currR-1, *currC);
		}
		
		//down
		if(g->data[*currR+1][*currC]==' ' && se->ParentR[*currR+1][*currC]==-2 && se->ParentC[*currR+1][*currC]==-2)
		{
			se->Distance[*currR+1][*currC] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR+1][*currC] = *currR;
			se->ParentC[*currR+1][*currC] = *currC;
			q->enqueue(*currR+1, *currC);
		}
		
		//left
		if(g->data[*currR][*currC-1]==' ' && se->ParentR[*currR][*currC-1]==-2 && se->ParentC[*currR][*currC-1]==-2)
		{
			se->Distance[*currR][*currC-1] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR][*currC-1] = *currR;
			se->ParentC[*currR][*currC-1] = *currC;
			q->enqueue(*currR, *currC-1);
		}
		
		//right
		if(g->data[*currR][*currC+1]==' ' && se->ParentR[*currR][*currC+1]==-2 && se->ParentC[*currR][*currC+1]==-2)
		{
			se->Distance[*currR][*currC+1] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR][*currC+1] = *currR;
			se->ParentC[*currR][*currC+1] = *currC;
			q->enqueue(*currR, *currC+1);
		}
	}
	
	if(q->size()==0 && g->data[*currR][*currC]!='G')
	{
		se->Length=-1;
		return se;
	}
	else
	{
		se->Length=se->Distance[*currR][*currC];
		se->s->push(*currR, *currC);
		//se->s->
		do
		{
			if(*currR!=-1 && *currC!=-1)
			{
				se->s->push(se->ParentR[*currR][*currC], se->ParentC[*currR][*currC]);
			}
			int tempR = *currR, tempC=*currC;
			*currR=se->ParentR[tempR][tempC];
			*currC=se->ParentC[tempR][tempC];	
		}while(*currR!=*startR || *currC!=*startC);
		
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


