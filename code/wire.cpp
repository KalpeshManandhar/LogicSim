#include "wire.h"
#include <iostream>


int Wire::totalWires = 0;
int Wire::selectedWireNo = -1;



Wire::Wire(){
    start = new Pin;
    end = new Pin;
    start->pos.x = -100;
    start->pos.y = -100;
    end->pos.x = -200;
    end->pos.y = -200;
    completeFlag = _ISBLANK;
    logic = -1;
}

Wire::~Wire(){

}


void Wire::addWire(Pin *startPin, Pin *endPin, int availableIndex){
    if (availableIndex == -1){
        index = totalWires;
        totalWires++;
    }
    else{
        index = availableIndex;
    }
    selectedWireNo = index;
    start = startPin;
    end = endPin;
    completeFlag = _INCOMPLETE;
    std::cout<<"Added wire "<<index<<std::endl;
    std::cout<<start->pos.x<<","<<start->pos.y<<std::endl;
}



void Wire::draw(SDL_Renderer * renderer){
    if (logic == 1)
        SDL_SetRenderDrawColor(renderer, 200, 0 , 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // if (completeFlag == _INCOMPLETE)
    //     SDL_RenderDrawLine(renderer, start->pos.x, start->pos.y, end.x, end.y);
    // else
    SDL_RenderDrawLine(renderer, start->pos.x, start->pos.y, end->pos.x, end->pos.y);
}


void Wire::completeWire(Pin * endPin){
    end = endPin;
    completeFlag = _COMPLETE;
}

wire_Condtion Wire::getStatus(){
    return(completeFlag);
}


void Wire::removeWire(){
    start->pos.x = -100;
    start->pos.y = -100;
    end->pos.x = -200;
    end->pos.x = -200;
    start->type = _BLANKE;
    end->type = _BLANKE;
    completeFlag = _ISBLANK;
    logic = -1;
    selectedWireNo = -1;
}


bool Wire::validWire(Pin * end){
    if (start->type == end->type)
        return(false);
    return(true);
}