#pragma once
#include "SDL2/SDL.h"

class Graphics {
	SDL_Window* window;
	SDL_Surface* loadingSurface;
	SDL_Renderer* renderer;
public:
	Graphics();
	~Graphics();
	void mainLoop();


};

