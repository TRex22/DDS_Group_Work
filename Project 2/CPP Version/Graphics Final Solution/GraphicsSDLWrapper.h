#ifndef _GRAPHICSSDLWRAPPER_H_
    #define _GRAPHICSSDLWRAPPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <SDL/SDL.h>

class Screen{
	public:
		SDL_Rect Rect;
		SDL_Surface* screen;
		SDL_Event event;
		
	public:
		Screen();
		~Screen();
		
		void Graphics_init();
		void delay();
		
		void CreateRectangle(SDL_Surface* screen, SDL_Rect *Rect, int x, int y, int h, int w, int colour);
		
		
		
};


#endif
