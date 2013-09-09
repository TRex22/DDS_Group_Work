#include <stdio.h>
#include <stdlib.h>

#include "Grid.h"

#include "LinkList.h"
#include "Stack.h"
#include "Queue.h"

/* ------------- QUEUE FUNCTIONS ------------------ */
Queue* queue_init(){
	Queue *q=(Queue*)malloc(sizeof(Queue));
	q->l=ll_init();
	return q;
}
void queue_free(Queue *q){
	ll_free(q->l);
	free(q);
}

void queue_enqueue(Queue *q, int x, int y){
	ll_addBack(q->l, x, y);
}

void queue_dequeue(Queue *q, int *x, int *y){
	ll_getFront(q->l, x, y);
}

int queue_size(Queue *q){
	return ll_size(q->l);
}


/* ------------- STACK FUNCTIONS ------------------ */
Stack* stack_init(){
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->l=ll_init();
	return s;
}
void stack_free(Stack *s){
	ll_free(s->l);
	free(s);
}

void stack_push(Stack *s, int x, int y){
	ll_addFront(s->l, x, y);
}

//will add if need be
//with code provided the only way to peek
//is to get front then add front
//void stack_peek(Stack *s, int *x, int *y){	
//}

void stack_pop(Stack *s, int *x, int *y){
	ll_getFront(s->l, x, y);
}

int stack_size(Stack *s){
	return ll_size(s->l);
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
	//Pseudocode used to find shortest path using breadth first search algorithm provided
	//by the project pack.
	
	//new queue
	Queue *q = queue_init();	
	//new stack
	Stack *s = stack_init();

	//Initialise ParentR[Num Rows][Num Cols] to -2;
	//Initialise ParentC[Num Rows][Num Cols] to -2;
	//Initialise Distance[Num Rows][Num Cols] to MAX INT;

	//Distance[startR][startC] ← 0;
	//ParentR[startR][startC] ← -1;
	//ParentC[startR][startC] ← -1;

	//Enqueue(q, startR, startC);
	//while q isn’t empty and we haven’t discovered the goal do
		//currR, currC ← Dequeue(q);

		//if world[currR-1][currC] is open and undiscovered then
				//Distance[currR-1][currC] = Distance[currR][currC] + 1;
				//ParentR[currR-1][currC] = currR;
				//ParentC[currR-1][currC] = currC;
				//Enqueue(q, currR-1, currC);
		//end if

		//if world[currR+1][currC] is open and undiscovered then
				//Distance[currR+1][currC] = Distance[currR][currC] + 1;
				//ParentR[currR+1][currC] = currR;
				//ParentC[currR+1][currC] = currC;
				//Enqueue(q, currR+1, currC);
		//end if

		//if world[currR][currC-1] is open and undiscovered then
				//Distance[currR][currC-1] = Distance[currR][currC] + 1;
				//ParentR[currR][currC-1] = currR;
				//ParentC[currR][currC-1] = currC;
				//Enqueue(q, currR, currC-1);
		//end if

		//if world[currR][currC+1] is open and undiscovered then
				//Distance[currR][currC+1] = Distance[currR][currC] + 1;
				//ParentR[currR][currC+1] = currR;
				//ParentC[currR][currC+1] = currC;
				//Enqueue(q, currR, currC+1);
		//end if
	//end while

	//if the queue is empty and we never found the goal then
		//return No Path to goal
	//else
		//currR, currC ← goalR, goalC;
		//while we haven’t reached the source do
			//Push(s, ParentR[currR][currC], ParentC[currR][currC]);
			//currR, currC ← ParentR[currR][currC], ParentC[currR][currC];
		//end while
		// Popping items off of S will give the path in the correct order
		//return the stack, s.
	//end if
//end function
	

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



