#include "graphics.h"
#include "input.h"
#include "component.h"
#include <iostream>

#define WIN_HEIGHT 720
#define WIN_WIDTH 1280

#define FPS 32
#define FRAME_LIMIT (1000/FPS)

Component components[MAX_COMPONENTS];

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
        std::cout<<"Error creating renderer"<<SDL_GetError()<<std::endl;
        
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
    loadSpriteAndGrid();
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
        input.getMouseState();
        input.handleMouseInput();
        clearScreen(68,75,110, false);
        componentLoad();
        drawComponents();
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
    SDL_SetRenderDrawColor(renderer, r,g,b,255);
    SDL_RenderClear(renderer); 
     
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
void Graphics::drawComponents()
{
    int i;
    for(i=0; i<Component::componentNo;i++){
        if (components[i].getType() != _NOTHING)
            components[i].draw(renderer, textureOfGates);
    }
}

SDL_Renderer* Graphics::getRenderer(){
    return(renderer);
}

SDL_Texture* Graphics::getTexture(){
    return(textureOfGates);
}

void Graphics::componentLoad()
{
    int shift=50;
    SDL_Rect source = {0,0,146,72}, destination = {0,620,(int)(146*0.7),(int)(72*0.7)};
    c_type type;
    for(short i=0;i<5;i++)
    {
        source.x = i*146;
        destination.x = shift + i*146;
        SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
    }
}