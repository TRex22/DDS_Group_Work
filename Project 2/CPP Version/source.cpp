#include <stdio.h>
#include <stdlib.h>

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


