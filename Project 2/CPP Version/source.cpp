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
	l=new LinkList();
	//size =0;
	//return q;
	
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
		return;
	}
	else
	{
		l->getFront(x, y);
	}
	
}

int Queue::size(){
	return size();
}

/* ------------- STACK FUNCTIONS ------------------ */
Stack::Stack(){
	//size = 0;
	l = new LinkList();
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
		return;
	}
	else
	{
		l->getFront(x, y);
	}
}

int Stack::size(){
	return size();
}

/* ------------- SEARCH FUNCTIONS ------------------ */
Grid* ReadWorld(const char* filename){

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


