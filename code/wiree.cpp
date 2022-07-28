#include "wire.h"
#include "component.h"
#include <iostream>


int Wire::totalWires = 0;
int Wire::selectedWireNo = -1;



Wire::Wire(){
    start.x = -100;
    start.y = -100;
    end->x = -200;
    end->y = -200;
    completeFlag = _ISBLANK;
    logic = -1;
}

Wire::~Wire(){
    
}



void Wire::addWire(vec2 startPoint, vec2 *endPoint, int availableIndex){
    if (availableIndex == -1){
        wires[totalWires] = new Wire;
        index = totalWires;
        totalWires++;
    }
    else{
        index = availableIndex;
    }
    selectedWireNo = index;
    start = startPoint;
    end = endPoint;
    completeFlag = _INCOMPLETE;
    std::cout<<"Added wire "<<index<<std::endl;
    std::cout<<start.x<<","<<start.y<<std::endl;
}



void Wire::draw(SDL_Renderer * renderer){
    if (logic == 1)
        SDL_SetRenderDrawColor(renderer, 200, 0 , 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // if (completeFlag == _INCOMPLETE)
    //     SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    // else
    SDL_RenderDrawLine(renderer, start.x, start.y, end->x, end->y);
}


void Wire::completeWire(){
    completeFlag = _COMPLETE;
}

wire_Condtion Wire::getStatus(){
    return(completeFlag);
}


void Wire::removeWire(){
    start.x = -100;
    start.y = -100;
    end->x = -200;
    end->x = -200;
    completeFlag = _ISBLANK;
    logic = -1;
    selectedWireNo = -1;
}