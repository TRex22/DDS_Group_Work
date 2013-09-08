#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#define BLOCK 'x'
#define TRUE 1
#define FALSE 0
/* Point in the maze */
struct point{
    int r;
    int c;
};
typedef struct point POINT;

/* Function Prototypes */
int search(char** maze, int row, int col, int, int, SDL_Surface*, SDL_Rect, int, int);
char** InitMaze(int*, int*);
void printMaze(char** maze, int rows, int cols, SDL_Surface*, SDL_Rect, int, int);
char** readMaze(int* rows, int* cols);
void CreateRectangle(SDL_Surface*, SDL_Rect *, int, int, int, int, int);

POINT start;
POINT goal;

int main(int argc, char* args[]){
    int rows, cols;
    char** maze;

    maze = InitMaze(&rows, &cols);
    //primitives
	int i, j, OSC;
	int SCREEN_WIDTH, SCREEN_HEIGHT, rectH, rectW, noRect;
	SCREEN_WIDTH = (cols+2)*10;
    SCREEN_HEIGHT = (rows+2)*10;
	rectW = cols+200;
    rectH = rows+200;
	SDL_Rect Rect;
	SDL_Surface* screen;
	SDL_Event event;
	Uint32 flags = SDL_SWSURFACE|SDL_FULLSCREEN;
	SDL_Init( SDL_INIT_EVERYTHING ); 
	freopen("CON", "w", stdout); //enable console output
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE );
	//This will not draw directly to the sceen. You must call flip to actually see the results of the drawing
	//caption = "First World!\0";
	SDL_WM_SetCaption ("Maze!", NULL);
	SDL_PollEvent (&event);
	switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
		        printf( "Key press detected\n" );
		        exit(0);
		        break;
	
	      	case SDL_KEYUP:
		        printf( "Key release detected\n" );
		        exit(0);
		        break;
				
			//case 
		}
    printMaze(maze, rows, cols, screen, Rect, rectH, rectW);
    if(search(maze, rows, cols, start.r, start.c, screen, Rect, rectH, rectW))
        printf("FOUND!\n");
}

void delay(){
   long i = 0;
    for(i = 0; i < 1000000L;i++); 

}

int search(char** maze, int rows, int cols, int r, int c, SDL_Surface* screen, SDL_Rect Rect, int rectH, int rectW){
    if(r < 0 || c > cols)
        return FALSE;

    if(maze[r][c] == 'G'){
        return TRUE;
    }
    delay();
    if(maze[r][c] == ' '){
        maze[r][c] = '.';
        //printMaze(maze, rows, cols);
        printMaze(maze, rows, cols, screen, Rect, rectH, rectW);
        printf("Checking: %d %d\n", r, c);

        maze[r][c] = '|';
        if(search(maze, rows, cols, r-1, c, screen, Rect, rectH, rectW))
            return TRUE;
        maze[r][c] = '|';
        if(search(maze, rows, cols, r+1, c, screen, Rect, rectH, rectW))
            return TRUE;
        maze[r][c] = '-';
        if(search(maze, rows, cols, r, c-1, screen, Rect, rectH, rectW))
            return TRUE;
        maze[r][c] = '-';
        if(search(maze, rows, cols, r, c+1, screen, Rect, rectH, rectW))
            return TRUE;

        maze[r][c] = ' ';
    }
    printMaze(maze, rows, cols, screen, Rect, rectH, rectW);
    printf("Checking: %d %d\n", r, c);
    delay();
    return FALSE;
}


char** InitMaze(int* rows, int* cols){
    int i,j;
    // Read the maze from the file
    char** out = readMaze(rows, cols);

    // Replace and 'x' characters with the BLOCK char
    for(i = 0; i < *rows; i++)
        for(j = 0; j < *cols; j++){
            if(out[i][j] == 'x')
                out[i][j] = BLOCK;
            if(out[i][j] == 'S'){
                (start).r = i;
                (start).c = j;
                out[i][j] = ' ';
            }
            if(out[i][j] == 'G'){
                (goal).r = i;
                (goal).c = j;
            }
        
        }

    // Return the array
    return out;
}

char** readMaze(int* rows, int* cols){
    int i,j;
    FILE *f;
    char** out;

    // Open the Maze File for Reading
    f = fopen("maze.txt", "r");
    // Read the two integers from the first line
    fscanf(f, "%d %d\n", rows, cols);

    // Allocate space for the 2D char array
    out = (char**) malloc(*rows * sizeof(char*));
    for(i = 0; i < *rows; i++)
        // An extra 2 chars are allocated for the \n and the \0 characters
        out[i] = (char*) malloc((*cols+2) * sizeof(char));

    // Read each line from the file
    for(i = 0; i < *rows; i++)
        fgets(out[i], *cols+2, f);

    // Return the 2D char array, this is safe as it is allocated on the heap, not the stack.
    return out;
}

void printMaze(char** maze, int rows, int cols, SDL_Surface* screen, SDL_Rect Rect, int RectH, int RectW){
    int i,j, x, y, h = 1, k = 1;;
    //system("cls");
    printf("Start:\t %d %d\nGoal:\t %d %d\n", start.r, start.c, goal.r, goal.c );

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%c", maze[i][j]);
            x = (j+h);
			y = (i+k);
			
			if (maze[i][j]== 'x')
            {
            	//its alive point
            	//ie a colour not the background / 0
            	CreateRectangle(screen, &Rect, x, y, RectH, RectW, 4);
            }
            else if (maze[i][j]== ' ')
            {
            	//assume its dead ie if its a border or a blank space
            	//or anything unexpected
            	//must be painted as background 0
            	CreateRectangle(screen, &Rect, x, y, RectH, RectW, 0);
            }
            else if (maze[i][j]== '-' || maze[i][j]== '|')
            {
            	//assume its dead ie if its a border or a blank space
            	//or anything unexpected
            	//must be painted as background 0
            	//CreateRectangle(screen, &Rect, x, y, RectH, RectW, 3);
            	CreateRectangle(screen, &Rect, x, y, RectH, RectW, 3);
            }
            else //if (maze[i][j]== '!')
            {
            	//its alive point
            	//ie a colour not the background / 0
            	CreateRectangle(screen, &Rect, x, y, RectH, RectW, 2);
            }
            //CreateRectangle(screen, &Rect, x, y, RectH, RectW, 3);
            SDL_Flip(screen);
            h = j*10;
            k = i*10;
        }
        delay();
        printf("\n");
    }
}

void CreateRectangle(SDL_Surface* screen, SDL_Rect *Rect, int x, int y, int h, int w, int colour)
{
	//Set the dimesions of the rectangle
	Rect -> x = x;
	Rect -> y = y;
	Rect -> h = h;
	Rect -> w = w;
	//determine the colour required:
		//0 is for black
		//1 is for white
	switch(colour)
	{
		//black
		case 0:
		{
			//fill the rectangle
			SDL_FillRect(screen,Rect,SDL_MapRGB(screen -> format,0,0,0));
			break;
		} 
		//white
		case 1:
		{
			//fill the rectangle
			SDL_FillRect(screen,Rect,SDL_MapRGB(screen -> format,255,255,255));
			break;
		}
		//have other cases programmed for future changes like green and blue
		//red
		case 2:
		{
			//fill the rectangle
			SDL_FillRect(screen,Rect,SDL_MapRGB(screen -> format,255,0,0));
			break;
		}	
		//green
		case 3:
		{
			//fill the rectangle
			SDL_FillRect(screen,Rect,SDL_MapRGB(screen -> format,0,255,0));
			break;
		}	
		//blue
		case 4:
		{
			//fill the rectangle
			//if (rand()%2 == 1)
			//{
				SDL_FillRect(screen,Rect,SDL_MapRGB(screen -> format,0,0,255));
			//}
			//else
			//{
				//SDL_FillRect(screen,Rect,SDL_MapRGB(screen -> format,0,0,55));	
			//}				
			break;
		}
		
	}
}
