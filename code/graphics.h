#pragma once
#include "utils.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

enum{
	CLOSED, 
};


class Graphics {
	SDL_Window *window;
	SDL_Surface *loadingSurface;
	SDL_Texture *textureOfGates;
	SDL_Renderer *renderer;
	bool isRunning;
	vec2 windowSize;
	load_type compLoadType;
public:


	Graphics();
	~Graphics();
	int mainLoop();
	Uint32 getTime();
	
	void delay(Uint32 ms);
	void display();
	void loadSpriteAndGrid();
	void clearScreen();

	void drawComponents();
	void drawWires();
	void callLogic();

	SDL_Renderer* getRenderer();
	SDL_Texture* getTexture();
	void componentLoad();
	void getWindowSize();
};

