#include "graphics.h"
#include "input.h"
#include "component.h"
#include "wire.h"
#include "logic.h"
#include <iostream>

#define WIN_HEIGHT 760
#define WIN_WIDTH 1440

#define FPS 60
#define FRAME_LIMIT (1000/FPS)

Component *components[MAX_COMPONENTS];
Wire *wires;

Button gate = {0,0,25,15, true};
Button comb = {0,0,25,15,false};
Button ff = {0,0,25,15,false};

int comp_spawn[13][4];

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
    windowSize.x = WIN_WIDTH;
    windowSize.y = WIN_HEIGHT;
    compLoadType = _GATES;
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
        case SDL_WINDOWEVENT:{
            getWindowSize();
        }
        default:
            break;
        }

        // handle mouse inputs
        input.getMouseState();
        input.handleMouseInput(windowSize, compLoadType);

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
    loadingSurface = IMG_Load("assets/spritesheet.png");
    textureOfGates = SDL_CreateTextureFromSurface(renderer,loadingSurface);
    SDL_FreeSurface(loadingSurface);
    loadingSurface = IMG_Load("assets/grid_new.png");
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
    gate.button.x = X_BOUND(windowSize.x) - 10;
    gate.button.y = Y_BOUND(windowSize.y) - 55;
    comb.button.x = X_BOUND(windowSize.x) - 10;
    comb.button.y = Y_BOUND(windowSize.y) - 30;
    ff.button.x = X_BOUND(windowSize.x) - 10;
    ff.button.y = Y_BOUND(windowSize.y) - 5;
    
    gate.draw(renderer);
    comb.draw(renderer);
    ff.draw(renderer);

    static SDL_Rect source = {0,0,146,72}, destination = {0,Y_BOUND(windowSize.y)-60,(int)(146*0.7),(int)(72*0.7)};
    int num = (compLoadType == _GATES)?9:8;
    int shift = (X_BOUND(windowSize.x) - 10 - num * destination.w)/(num+1);
    short i = 0;
    if (compLoadType == _GATES)
        for(i=0;i< 7;i++){
            source.x = (i%5)*146;
            source.y = (i/5)*72;
            destination.x = shift + (shift + destination.w)* (i);
            destination.y = Y_BOUND(windowSize.y)-45;
            comp_spawn[i][0]=destination.x;
            comp_spawn[i][1]=destination.y;
            comp_spawn[i][2]=destination.w;
            comp_spawn[i][3]=destination.h;
            SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
        }
    else if (compLoadType == _COMBINATIONAL){
        for(i=0;i< 6;i++){
            source.x = (i%5)*146;
            source.y = (i/5+2)*72;
            destination.x = shift + (shift + destination.w)* (i);
            destination.y = Y_BOUND(windowSize.y)-45;
            comp_spawn[i][0]=destination.x;
            comp_spawn[i][1]=destination.y;
            comp_spawn[i][2]=destination.w;
            comp_spawn[i][3]=destination.h;
            SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
        }
    }
    else {
        for(i=0;i< 6;i++){
            source.x = (i%5)*146;
            source.y = (i/5+4)*72;
            destination.x = shift + (shift + destination.w)* (i);
            destination.y = Y_BOUND(windowSize.y)-45;
            comp_spawn[i][0]=destination.x;
            comp_spawn[i][1]=destination.y;
            comp_spawn[i][2]=destination.w;
            comp_spawn[i][3]=destination.h;
            SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
        }
    }
    source.y = 72;
    source.x = 2*146;
    destination.x = shift + (shift + destination.w)* ((i++%10));
    comp_spawn[7][0] = destination.x;
    comp_spawn[7][1]=destination.y;
    comp_spawn[7][2]=destination.w;
    comp_spawn[7][3]=destination.h;
    SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
    source.x = 3*146;
    destination.x = shift + (shift + destination.w)* ((i%10));
    comp_spawn[8][0] = destination.x;
    comp_spawn[8][1]=destination.y;
    comp_spawn[8][2]=destination.w;
    comp_spawn[8][3]=destination.h;
    SDL_RenderCopy(renderer, textureOfGates, &source, &destination);
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
    bool clockPulse;
    int i,j,k,l;
    // loops twice as components aren't stored in order of connection 
    // that caused the logic to be wrong on some frames when input changed
    for (k = 0; k<1; k++){
        for (i = 0; i<Component::componentNo; i++){
            switch(components[i]->getType()){
                case _INPUT:
                    break;
                // updates the clock
                case _CLOCK:
                    components[i]->setOutput(FPS);
                    break;
                // computes the logic for the component
                default:
                    components[i]->setOutput(logicHandler.handleLogic(components[i]->getType(), components[i]->getInputs(), components[i]->getOutputs()));
                    break;
            }

            // updates the corresponding inputs from outputs
            for (j = 0; j<Wire::totalWires; j++){
                for (l=0; l< components[i]->getOutputNo(); l++){
                    if (components[i]->sendOutput()){
                        if (wires[j].getStatus() == _COMPLETE)
                            wires[j].sendLogic(components[i]->getOutPinAddress(l), -1);
                    }
                    else{
                        if (wires[j].getStatus() == _COMPLETE)
                            wires[j].sendLogic(components[i]->getOutPinAddress(l), 0);
                    }
                }
            }
        }   
    }
}


void Graphics::getWindowSize(){
    SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
}

// 0 for width 1 for height
int Graphics::windowDim(int a){
    if (a == 0)
        return(windowSize.x);
    return(windowSize.y);
}