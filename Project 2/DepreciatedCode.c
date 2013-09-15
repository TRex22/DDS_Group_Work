//Depreciated code
/* Jason's code
	//Pseudocode used to find shortest path using breadth first search algorithm provided
	//by the sproject pack.
	
	int i, j, count = 1;	
	
	//new queue
	Queue *q = queue_init();	
	//new stack
	Search *s = (Search*)malloc(sizeof(Search));
	s->s=stack_init();

	//Initialise ParentR[Num Rows][Num Cols] to -2;
	s->ParentR = (int**)malloc(sizeof(int*)*g->rows);
		for(i=0;i<g->rows;i++)
		{
			s->ParentR[i]=(int*)malloc(sizeof(int)*g->cols);
			s->ParentR[i]=-2;		
		}
	
	//Initialise ParentC[Num Rows][Num Cols] to -2;
	s->ParentC = (int**)malloc(sizeof(int*)*g->rows);
		for(j=0;j<g->rows;j++)
		{
			s->ParentC[i]=(int*)malloc(sizeof(int)*g->cols);
			s->ParentC[i]=-2;			
		}
	//Initialise Distance[Num Rows][Num Cols] to MAX INT;
	s->Distance = (int**)malloc(sizeof(int*)*g->rows);
		for(i=0;i<g->rows;i++)
		{
			s->Distance[i]=(int*)malloc(sizeof(int*)*g->cols);		
			s->Distance[i]=MAX_INT;
		}

	//Distance[startR][startC] ← 0;
	s->Distance[0]=0;
	//ParentR[startR][startC] ← -1;
	s->ParentR[0]=-1;
	//ParentC[startR][startC] ← -1;
	s->ParentC[0]=-1;
	//printf("Hello\n");
	
	//Enqueue(q, startR, startC);
	queue_enqueue(q, s->ParentR[0], s->ParentC[0]);
	//while q isn’t empty and we haven’t discovered the goal do
	while(q != NULL)
	{
		//currR, currC ← Dequeue(q);
		queue_dequeue(q, s->ParentR[count], s->ParentC[count]);
		//if world[currR-1][currC] is open and undiscovered then
		//if 
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
		count++;
	//end while
	}
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
	
*/
