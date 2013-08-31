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
	ll_addBack(q->l, x, y)
}

void queue_dequeue(Queue *q, int *x, int *y){
	
}

int queue_size(Queue *q){

}

/* ------------- STACK FUNCTIONS ------------------ */
Stack* stack_init(){

}
void stack_free(Stack *s){

}

void stack_push(Stack *s, int x, int y){

}

void stack_pop(Stack *s, int *x, int *y){

}

int stack_size(Stack *s){

}

/* ------------- SEARCH FUNCTIONS ------------------ */
Grid* ReadWorld(const char* filename){

}

Search* FindPath(Grid* g){


}

