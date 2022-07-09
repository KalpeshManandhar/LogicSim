#include "graphics.h"
#include "input.h"
#include "component.h"
#include <iostream>

#define WIN_HEIGHT 720
#define WIN_WIDTH 1280

#define FPS 40
#define FRAME_LIMIT (1000/FPS)

#define MAX_COMPONENTS 25

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
    loadSpriteAndGrid();
    
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
    Component components;
    // source={0,0,215,108};destination={input.mousePos.x, input.mousePos.y,600,300};
    Uint32 frameStart;    
    int frameTime;    
    while(isRunning){
        frameStart = getTime();
        switch (input.pollEvents())
        {
        case SDL_QUIT:
            isRunning = false;
            return(CLOSED);
        case SDL_MOUSEBUTTONDOWN:{
            input.getMouseState();
        }

        default:
            break;
        }
        // destination={input.mousePos.x-215/2,input.mousePos.y-108/2,215,108};
        clearScreen(68,75,110, false);
        drawComponent(true);
        display();
        
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

void Graphics::clearScreen(Uint8 r, Uint8 g, Uint8 b, bool grid){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, r,g,b,255);    
    if(grid)
        SDL_RenderCopy(renderer,textureOfGrid,NULL,NULL);
    
}
void Graphics::loadSpriteAndGrid()
{    
    loadingSurface = IMG_Load("assets/spritesheet.png");
    textureOfGates=SDL_CreateTextureFromSurface(renderer,loadingSurface);
    SDL_FreeSurface(loadingSurface);
    loadingSurface=IMG_Load("assets/grid_new.png");
    textureOfGrid=SDL_CreateTextureFromSurface(renderer,loadingSurface);
    SDL_FreeSurface(loadingSurface);    
}
void Graphics::drawComponent(bool draw)
{
    if(draw)
    {
        SDL_RenderCopy(renderer,textureOfGates,&source,&destination);
    }
    else 
        return;
}

SDL_Renderer* Graphics::getRenderer(){
    return(renderer);
}

SDL_Texture* Graphics::getTexture(){
    return(textureOfGates);
}