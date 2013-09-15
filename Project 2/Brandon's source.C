# include <stdio.h>
# include <stdlib.h>

# include "Grid.h"

# include "LinkList.h"
# include "Stack.h"
# include "Queue.h"


void FillRect(int , int , int , int , int, SDL_Surface*);
void graphic();

/* ------------- QUEUE FUNCTIONS ------------------ */
Queue* queue_init(){       
    Queue *newQueue = (Queue*) malloc(sizeof(Queue));
    newQueue->l = ll_init();    
    return newQueue;

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
    Stack *newStack = (Stack*) malloc(sizeof(Stack));
    newStack->l = ll_init();
    
    return newStack;
}
void stack_free(Stack *s){
     ll_free(s->l);
     free(s);
}

void stack_push(Stack *s, int x, int y){
     ll_addFront(s->l, x, y);
}

void stack_pop(Stack *s, int *x, int *y){
     ll_getFront(s->l, x, y);
}

int stack_size(Stack *s){
    return ll_size(s->l);
}

/* ------------- SEARCH FUNCTIONS ------------------ */
Grid* ReadWorld(const char* filename){
	Grid *mapInfo;
	int i;
	FILE *text;
	
	mapInfo = (Grid*) malloc (sizeof(Grid));
	
	text = fopen(filename, "r");
	
	fscanf(text, "%d %d\n", &mapInfo->rows, &mapInfo->cols);
	
	mapInfo->data = (char**) malloc(sizeof(char*)* mapInfo->rows);
	
	for(i=0;i<mapInfo->rows;i++)
		mapInfo->data[i] = (char*) malloc(sizeof(char)* mapInfo->cols);
	
	for(i=0; i<mapInfo->rows;i++)
		fgets(mapInfo->data[i], mapInfo->cols+2, text);
		
	
		return mapInfo;
}

Search* FindPath(Grid* g){
	
	
	
	Queue *q;
	q  = queue_init();
	Search *Struc;
	
	Struc = (Search*) malloc(sizeof(Search));
	
	Struc->s = stack_init();
	
	int i=0, j=0;
	
	Struc->ParentR = (int**) malloc(sizeof(int*) * g->rows);
	for(i=0;i<g->rows;i++)
		Struc->ParentR[i] = (int*) malloc(sizeof(int) * g->cols);
		
	
	Struc->ParentC = (int**) malloc(sizeof(int*) * g->rows);
	for(i=0;i<g->rows;i++)
		Struc->ParentC[i] = (int*) malloc(sizeof(int) * g->cols);
		
	Struc->Distance = (int**) malloc(sizeof(int*) * g->rows);
	for(i=0;i<g->rows;i++)
		Struc->Distance[i] = (int*) malloc(sizeof(int) * g->cols);
	
	for(i=0;i<g->rows;i++){
		for(j =0; j<g->cols;j++){
			Struc->ParentR[i][j] = -2;
		}
		
	}
	
	for(i=0;i<g->rows;i++){
		for(j =0; j<g->cols;j++){
			Struc->ParentC[i][j] = -2;
		}
		
	}
	
	for(i=0;i<g->rows;i++){
		for(j =0; j<g->cols;j++){
			Struc->Distance[i][j] = MAX_INT;
		}
		
	} 
	
	
	int startR = -1, startC = -1;
	int goalR = -200, goalC = -200;
	int currR = -100, currC = -100;
	
	
	//printf("hello\n");
	
	for(i=0;i<g->rows;i++){		
		for(j=0;j<g->cols;j++){
			if(g->data[i][j] == 'S'){
				startC = j;
				startR = i;
			}
		}
	}
	//printf("This is StartC %d and StartR %d\n", startC, startR);
	//printf("hello\n");
	Struc->Distance[startR][startC] = 0;
	Struc->ParentR[startR][startC] = -1;
	Struc->ParentC[startR][startC] = -1;
	queue_enqueue(q, startR, startC);
	
	while((queue_size(q) != 0) && (goalR < 0) && (goalC < 0)){
		queue_dequeue(q, &currR, &currC);
	/*	for(i=0;i<g->rows;i++){
			for(j=0;j<g->cols;j++){
				printf("[%d-%d\t]", Struc->ParentR[i][j], Struc->ParentC[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");*/
			
	//printf("hello1\n");
		if(g->data[currR][currC] == 'G'){
			goalR = currR;
			goalC = currC;
		}		
		if(((g->data[currR-1][currC] == ' ') || (g->data[currR-1][currC] == 'G')) && ((Struc->ParentR[currR-1][currC] == -2) && (Struc->ParentC[currR-1][currC] == -2))){
			Struc->Distance[currR-1][currC] = Struc->Distance[currR][currC]+ 1;
			Struc->ParentR[currR-1][currC] = currR;
			Struc->ParentC[currR-1][currC] = currC;
			queue_enqueue(q,currR-1,currC);
		} 
		 if(((g->data[currR+1][currC] == ' ')|| (g->data[currR+1][currC] == 'G')) && ((Struc->ParentR[currR+1][currC] == -2) && (Struc->ParentC[currR+1][currC] == -2))){
			Struc->Distance[currR+1][currC] = Struc->Distance[currR][currC]+ 1;
			Struc->ParentR[currR+1][currC] = currR;
			Struc->ParentC[currR+1][currC] = currC;
			queue_enqueue(q,currR+1,currC);
		}
		 if(((g->data[currR][currC-1] == ' ')|| (g->data[currR][currC-1] == 'G')) && ((Struc->ParentR[currR][currC-1] == -2) && (Struc->ParentC[currR][currC-1] == -2))){
			Struc->Distance[currR][currC-1] = Struc->Distance[currR][currC]+ 1;
			Struc->ParentR[currR][currC-1] = currR;
			Struc->ParentC[currR][currC-1] = currC;
			queue_enqueue(q,currR,currC-1);
		}
		 if(((g->data[currR][currC+1] == ' ') || (g->data[currR][currC+1] == 'G')) && ((Struc->ParentR[currR][currC+1] == -2) && (Struc->ParentC[currR][currC+1] == -2)))	{
			Struc->Distance[currR][currC+1] = Struc->Distance[currR][currC]+ 1;
			Struc->ParentR[currR][currC+1] = currR;
			Struc->ParentC[currR][currC+1] = currC;
			queue_enqueue(q,currR,currC+1);
		}
			
			
	}
	//printf("The startR %d the startC %d\n", startR, startC);
	//printf("The goalR %d and goalC %d\n", goalR, goalC);
	/*
	printf("\t");
	for(j=0;j<g->cols;j++)
		printf("[%d\t]", j);
		
		printf("\n");
	for(i=0;i<g->rows;i++){
		printf("[%d\t]", i);
			for(j=0;j<g->cols;j++){
				printf("[%d-%d\t]", Struc->ParentR[i][j], Struc->ParentC[i][j]);
			}
			printf("\n");
		
	} */
	//printf("The followingis the goalR %d and goalC %d\n", goalR, goalC);
	//printf("hello\n");
	
	if((queue_size(q) == 0) && (goalR < 0) && (goalC < 0)){
		Struc->Length = -1;
		//printf("hello6\n");
		return Struc;
			
	}
	else{
		//printf("hello2\n");
		currR = goalR;
		currC = goalC;
		//printf("The following is [%c]\n", g->data[currR][currC]);
		Struc->Length = Struc->Distance[currR][currC];
		//printf("This is the distance %d\n", Struc->Distance[currR][currC]);
		stack_push(Struc->s,goalR, goalC);
		
		
		int tmp;
		do{
			//printf("hello3\n");
			//printf("[%d]This is curr coming in [%d,%d\t] this is stack values[%d\t,%d]\n",i++, currR, currC,Struc->ParentR[currR][currC], Struc->ParentC[currR][currC]);
			if((currR != -1) && (currC != -1))
			stack_push(Struc->s, Struc->ParentR[currR][currC], Struc->ParentC[currR][currC]);
			tmp = currR;
			currR = Struc->ParentR[tmp][currC];
			currC = Struc->ParentC[tmp][currC];	
			//printf("The following is[%d\t,%d] , this is curr[%d,%d\t]\n", Struc->ParentR[currR][currC], Struc->ParentC[currR][currC], currR, currC);
		}while((currR != startR) ||	(currC != startC));
				//printf("This is the distance %d\n",Struc->Distance[goalR][goalC]);
		return Struc;
	}
}
