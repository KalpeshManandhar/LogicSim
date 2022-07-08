#include "graphics.h"
#include "input.h"
#include <iostream>

#define WIN_HEIGHT 720
#define WIN_WIDTH 1280

#define FPS 24
#define FRAME_LIMIT (1000/FPS)

Graphics::Graphics(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        std::cout<<"Error initializing SDL"<<std::endl;
    }
    window = SDL_CreateWindow("Logic Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if(!window){
        std::cout<<"Error creating window"<<std::endl;
    }
    renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        std::cout<<"Error creating renderer"<<std::endl;
    }
    isRunning = true;
}

Graphics::~Graphics(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Uint32 Graphics::getTime(){
    return(SDL_GetTicks());
}

int Graphics::mainLoop(){
    Input input;
    Uint32 frameStart;    
    int frameTime;    
    //loadSprite();

    while(isRunning){
        frameStart = getTime();
        switch (input.pollEvents())
        {
        case SDL_QUIT:
            isRunning = false;
            return(CLOSED);
        default:
            break;
        }
        clearScreen(68,75,110);
        display();
        input.getMouseState();
        input.printMousePos();
        frameTime = getTime() - frameStart;
        if (frameTime < FRAME_LIMIT)
            delay(FRAME_LIMIT - frameTime);
    }
    return 0;
}

void Graphics::delay(Uint32 ms){
    SDL_Delay(ms);
}

void Graphics::display(){
    SDL_RenderPresent(renderer);
}

void Graphics::clearScreen(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetRenderDrawColor(renderer, r,g,b,255);
    SDL_RenderClear(renderer);
}
void Graphics::loadSprite()
{
    // SDL_Rect rectangle={0,0,122,128};
    // loadingSurface = IMG_Load("E:/Programming/Cpp/and.png");
    // texture=SDL_CreateTextureFromSurface(renderer,loadingSurface);
    // SDL_FreeSurface(loadingSurface);
    // SDL_RenderCopy(renderer,texture,NULL,&rectangle);
}