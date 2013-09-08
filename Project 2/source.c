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



