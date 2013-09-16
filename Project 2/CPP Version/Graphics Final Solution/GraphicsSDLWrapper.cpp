//Graphics SDL Wrapper by Jason Chalom 2013

#include "GraphicsSDLWrapper.h"

Screen::Screen()
{
	
}

Screen::~Screen()
{
	
}

void Screen::Graphics_init()
{
	Uint32 flags = SDL_SWSURFACE|SDL_FULLSCREEN;
	freopen("CON", "w", stdout); //enable console output
}

void Screen::delay()
{
	
}

void Screen::CreateRectangle(SDL_Surface* screen, SDL_Rect *Rect, int x, int y, int h, int w, int colour)
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

