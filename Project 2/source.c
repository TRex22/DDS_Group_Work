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
	if(q->l != NULL)
	{
		ll_free(q->l);
	}
    q->l = NULL;
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
	//Ariels code broken
	/*Grid* g=(Grid*)malloc(sizeof(Grid));
	
	FILE *f=fopen(filename, "r");
	
	fscanf(f, "%d %d\n", g->rows, g->cols);
	
	g->data=(char**)malloc(g->rows*sizeof(char*));
	int i;
	for (i=0;i<g->rows;i++)
	{
		g->data[i]=(char*)malloc(g->cols*sizeof(char));
	}
	
	for (i=0;i<g->rows;i++)
	{
		fgets(g->data[i], g->cols+2, f);
	}
	
	fclose(f);
	
	return g;*/
	
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
	/*Queue* q=queue_init();
	//printf("1\n");
	Search* se=(Search*)malloc(sizeof(Search));
	//printf("2\n");
	se->s=stack_init();
	//printf("3\n");
	se->Length=0;
	//printf("4\n");
	
	se->ParentR=(int**)malloc(sizeof(int*));
	//printf("5\n");
	int i, j;
	for(i=0;i<g->rows;i++)
	{
		se->ParentR[i]=(int*)malloc(sizeof(int));
		printf("6\n");
		for(j=0;j<g->cols;j++)
		{	
			printf ("test i: %d j: %d\n",i,j);
			se->ParentR[i][j]=-2;
		}
	}
	printf("working here...");
	se->ParentC=(int**)malloc(sizeof(int*));
	printf("7\n");
	for(i=0;i<g->rows;i++)
	{
		se->ParentC[i]=(int*)malloc(sizeof(int));
		printf("8\n");
		for(j=0;j<g->cols;j++)
		{
			se->ParentC[i][j]=-2;
		}
	}

	se->Distance=(int**)malloc(sizeof(int*));
	printf("9\n");
	for(i=0;i<g->rows;i++)
	{
		se->Distance[i]=(int*)malloc(sizeof(int));
		printf("10\n");
		for(j=0;j<g->cols;j++)
		{
			se->Distance[i][j]=MAX_INT;
		}
	}
	
	i=0, j=0;
	int startR, startC;
	for(i=0;i<g->rows;i++)
	{
		for(j=0;j<g->cols;j++)
		{
			if(g->data[i][j]=='S')
			{
				startR=i;
				startC=j;
				break;
			}
		}
	}
	
	se->Distance[startR][startC]=0;
	se->ParentR[startR][startC]=-1;
	se->ParentC[startR][startC]=-1;
	
	queue_enqueue(q, startR, startC);
	
	int *currR, *currC;
	while(queue_size(q)!=0 && g->data[*currR][*currC]!='G')
	{
		queue_enqueue(q, *currR, *currC);
		
		//up
		if(g->data[*currR-1][*currC]==' ' && se->ParentR[*currR-1][*currC]==-2 && se->ParentC[*currR-1][*currC]==-2)
		{
			se->Distance[*currR-1][*currC] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR-1][*currC] = *currR;
			se->ParentC[*currR-1][*currC] = *currC;
			queue_enqueue(q, *currR-1, *currC);
		}
		
		//down
		if(g->data[*currR+1][*currC]==' ' && se->ParentR[*currR+1][*currC]==-2 && se->ParentC[*currR+1][*currC]==-2)
		{
			se->Distance[*currR+1][*currC] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR+1][*currC] = *currR;
			se->ParentC[*currR+1][*currC] = *currC;
			queue_enqueue(q, *currR+1, *currC);
		}
		
		//left
		if(g->data[*currR][*currC-1]==' ' && se->ParentR[*currR][*currC-1]==-2 && se->ParentC[*currR][*currC-1]==-2)
		{
			se->Distance[*currR][*currC-1] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR][*currC-1] = *currR;
			se->ParentC[*currR][*currC-1] = *currC;
			queue_enqueue(q, *currR, *currC-1);
		}
		
		//right
		if(g->data[*currR][*currC+1]==' ' && se->ParentR[*currR][*currC+1]==-2 && se->ParentC[*currR][*currC+1]==-2)
		{
			se->Distance[*currR][*currC+1] = se->Distance[*currR][*currC] + 1;
			se->ParentR[*currR][*currC+1] = *currR;
			se->ParentC[*currR][*currC+1] = *currC;
			queue_enqueue(q, *currR, *currC+1);
		}
	}
	
	if(queue_size==0 && g->data[*currR][*currC]!='G')
	{
		se->Length=-1;
		return se;
	}
	else
	{
		se->Length=se->Distance[*currR][*currC];
		stack_push(se->s, *currR, *currC);
		
		do
		{
			if(*currR!=-1 && *currC!=-1)
			{
				stack_push(se->s, se->ParentR[*currR][*currC], se->ParentC[*currR][*currC]);
			}
			int tempR = *currR, tempC=*currC;
			*currR=se->ParentR[tempR][tempC];
			*currC=se->ParentC[tempR][tempC];	
		}while(*currR!=startR || *currC!=startC);
		
		return se;
	}*/
	Queue* q=queue_init();
	//printf("1\n");
	Search* se=(Search*)malloc(sizeof(Search));
	//printf("2\n");
	se->s=stack_init();
	//printf("3\n");
	se->Length=0;
	//printf("4\n");
	
	int i=0, j=0, rows = g->rows, cols = g->cols;
	
	se->ParentR=(int**)malloc(sizeof(int*)*rows);
	//printf("5\n");
	
	//printf("Here\n");
	//printf("Rows %d\n", rows);
	//printf("i: %d",i);
	
	//system.end(0);
	
	for(i=0;i<rows;i++)
	{
		//break;
		//printf("Rows %d\n", rows);
		
		//system("sleep(1000)");
		//printf("%d\n",i);
		se->ParentR[i]=(int*)malloc(sizeof(int)*cols);
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
	se->ParentC=(int**)malloc(sizeof(int*)*rows);
	//printf("7\n");
	for(i=0;i<rows;i++)
	{
		se->ParentC[i]=(int*)malloc(sizeof(int)*cols);
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
	//printf("Test\n");
	se->Distance=(int**)malloc(sizeof(int*)*rows);
	//printf("9\n");
	
	for(i=0;i<rows;i++)
	{
		se->Distance[i]=(int*)malloc(sizeof(int)*cols);
		//printf("10\n");
		
	}
	
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			se->Distance[i][j]=MAX_INT;
		}
	}
	
	i=0, j=0;
	int startR, startC;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			if(g->data[i][j]=='S')
			{
				startR=i;
				startC=j;
				break;
			}
		}
	}
	
	se->Distance[startR][startC]=0;
	se->ParentR[startR][startC]=-1;
	se->ParentC[startR][startC]=-1;
	//printf("Rows: %d Cols: %d\n",rows,cols);
	//*q = enqueue(*startR, *startC);
	queue_enqueue(q, startR, startC);
	
	int currR, currC;
			//printf("hello\n");
	currR = startR;
	currC = startC;
	//printf("Rows: %d Cols: %d\n",rows,cols);
	//printf("queue size: %d\n",queue_size);
			//printf("hello\n");
	while((queue_size)!=0 && g->data[currR][currC]!='G')
	{

		//printf("Rows: %d Cols: %d\n",rows,cols);
		queue_enqueue(q, currR, currC);
		
		//up
		if(g->data[currR-1][currC]==' ' && se->ParentR[currR-1][currC]==-2 && se->ParentC[currR-1][currC]==-2)
		{
			se->Distance[currR-1][currC] = se->Distance[currR][currC] + 1;
			se->ParentR[currR-1][currC] = currR;
			se->ParentC[currR-1][currC] = currC;
			queue_enqueue(q, currR-1, currC);
		}
		
		//down
		if(g->data[currR+1][currC]==' ' && se->ParentR[currR+1][currC]==-2 && se->ParentC[currR+1][currC]==-2)
		{
			se->Distance[currR+1][currC] = se->Distance[currR][currC] + 1;
			se->ParentR[currR+1][currC] = currR;
			se->ParentC[currR+1][currC] = currC;
			queue_enqueue(q, currR+1, currC);
		}
		
		//left
		if(g->data[currR][currC-1]==' ' && se->ParentR[currR][currC-1]==-2 && se->ParentC[currR][currC-1]==-2)
		{
			se->Distance[currR][currC-1] = se->Distance[currR][currC] + 1;
			se->ParentR[currR][currC-1] = currR;
			se->ParentC[currR][currC-1] = currC;
			queue_enqueue(q, currR, currC-1);
		}
		
		//right
		if(g->data[currR][currC+1]==' ' && se->ParentR[currR][currC+1]==-2 && se->ParentC[currR][currC+1]==-2)
		{
			se->Distance[currR][currC+1] = se->Distance[currR][currC] + 1;
			se->ParentR[currR][currC+1] = currR;
			se->ParentC[currR][currC+1] = currC;
			queue_enqueue(q, currR, currC+1);
		}
	}
	
	if(queue_size==0 && g->data[currR][currC]!='G')
	{
		se->Length=-1;
		return se;
	}
	else
	{
		se->Length=se->Distance[currR][currC];
		stack_push(se->s, se->ParentR[currR][currC], se->ParentC[currR][currC]);
		//se->s->
		do
		{
			if(currR!=-1 && currC!=-1)
			{
				stack_push(se->s, se->ParentR[currR][currC], se->ParentC[currR][currC]);
			}
			int tempR = currR, tempC=currC;
			currR=se->ParentR[tempR][tempC];
			currC=se->ParentC[tempR][tempC];	
		}while(currR!=startR || currC!=startC);
		
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



