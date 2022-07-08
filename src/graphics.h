#pragma once
#include "SDL2/SDL.h"

enum{
	CLOSED, 
};


class Graphics {
	SDL_Window* window;
	SDL_Surface* loadingSurface;
	SDL_Renderer* renderer;
	bool isRunning;
public:
	Graphics();
	~Graphics();
	int mainLoop();
	Uint32 getTime();
	void delay(Uint32 ms);
	void display();
	void clearScreen(Uint8 r, Uint8 g, Uint8 b);

};

