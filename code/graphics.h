#pragma once
#include "SDL.h"
#include "SDL_image.h"

enum{
	CLOSED, 
};


class Graphics {
	SDL_Window *window;
	SDL_Surface *loadingSurface;
	SDL_Renderer *renderer;
	SDL_Texture *textureOfGates, *textureOfGrid;
	// SDL_Rect source, destination;
	bool isRunning;
public:
	Graphics();
	~Graphics();
	int mainLoop();
	Uint32 getTime();
	void delay(Uint32 ms);
	void display();
	void loadSpriteAndGrid();
	void clearScreen(Uint8 r, Uint8 g, Uint8 b, bool grid);
	void drawComponent(bool draw);
	SDL_Renderer* getRenderer();
	SDL_Texture* getTexture();
	
};

