#include "graphics.h"
#include "input.h"
#include "component.h"
#include "wire.h"
#include "logic.h"
#include <iostream>

#define WIN_HEIGHT 720
#define WIN_WIDTH 1280

#define FPS 32
#define FRAME_LIMIT (1000/FPS)

Component *components[MAX_COMPONENTS];
Wire *wires;


Graphics::Graphics(){
    wires = new Wire[MAX_WIRES];
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
    int i,j;        
    
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
        // handle mouse inputs
        input.getMouseState();
        input.handleMouseInput();

        // logic computation
        callLogic();

        // clear screen and draw the components/ wires
        clearScreen(68,75,110, false);        
        componentLoad();
        drawComponents();
        drawWires();

        // display to screen
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

// initial textures loading
void Graphics::loadSpriteAndGrid()
{    
    loadingSurface = IMG_Load("assets\\spritesheet.png");
    textureOfGates = SDL_CreateTextureFromSurface(renderer,loadingSurface);
    SDL_FreeSurface(loadingSurface);
    loadingSurface = IMG_Load("grid_new.png");
    textureOfGrid = SDL_CreateTextureFromSurface(renderer,loadingSurface);
    SDL_FreeSurface(loadingSurface);    
}

void Graphics::drawComponents(){
    int i;
    for(i=0; i<Component::componentNo;i++){
        if (components[i]->getType() != _NOTHING)
            components[i]->draw(renderer, textureOfGates);
    }
}

SDL_Renderer* Graphics::getRenderer(){
    return(renderer);
}

SDL_Texture* Graphics::getTexture(){
    return(textureOfGates);
}

// spawn area components
void Graphics::componentLoad()
{
    int shift=30;
    SDL_Rect source = {0,0,146,72}, destination = {0,620,(int)(146*0.7),(int)(72*0.7)};
    for(short i=0;i<9;i++){
        source.x = (i%5)*146;
        source.y = (i/5)*72;
        destination.x = shift + (shift + destination.w)* i ;
        SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
    }
}

void Graphics::drawWires(){
    int i;
    for(i=0; i<Wire::totalWires;i++){
        // draws wire if not blank
        if (wires[i].getStatus() != _ISBLANK)
            wires[i].draw(renderer);
    }
}

void Graphics::callLogic(){
    static Logic logicHandler;
    int i,j,k;
    // loops twice as components aren't stored in order of connection 
    // that caused the logic to be wrong on some frames when input changed
    for (k = 0; k<2; k++){
        for (i = 0; i<Component::componentNo; i++){
            if (components[i]->getType() != _INPUT){
                // updates the corresponding inputs from outputs
                for (j = 0; j<Wire::totalWires; j++){
                    if (wires[j].getStatus() == _COMPLETE)
                        wires[j].sendLogic();
                }
                // computes the logic for the component
                components[i]->setOutput(logicHandler.handleLogic(components[i]->getType(), components[i]->getInputs()));
            }
        }   
    }
}