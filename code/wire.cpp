#include "wire.h"
#include "component.h"
#include <iostream>


int Wire::totalWires = 0;
int Wire::selectedWireNo = -1;

Wire deadWire(1);


Wire::Wire(){
    start = new Pin;
    end = new Pin;
    start->pos = new vec2;
    end->pos = new vec2;
    start->logic = new int;
    end->logic =  new int;
    
    // start->pos = NULL;
    // end->pos = NULL;
    completeFlag = _ISBLANK;
}

Wire::Wire(int def){
    start = new Pin;
    end = new Pin;
    start->pos = new vec2;
    end->pos = new vec2;
    start->logic = new int;
    end->logic =  new int;
    start->pos->x = -200;
    start->pos->y = -200;
    end->pos->x = -200;
    end->pos->y = -200;

    completeFlag = _ISBLANK;
}

Wire::~Wire(){

}


void Wire::addWire(Pin *startPin, vec2 *endPoint, int availableIndex){

    if (availableIndex == -1){
        index = totalWires;
        totalWires++;
    }
    else{
        index = availableIndex;
    }
    selectedWireNo = index;


    start = startPin;
    end->pos = endPoint;
    completeFlag = _INCOMPLETE;
    std::cout<<"Added wire "<<index<<std::endl;
    std::cout<<start->pos->x<<","<<start->pos->y<<std::endl;
}



void Wire::draw(SDL_Renderer * renderer){
    if (completeFlag == _COMPLETE){
        if (*logic == 1)
            SDL_SetRenderDrawColor(renderer, 200, 0 , 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, start->pos->x, start->pos->y, end->pos->x, end->pos->y);
}


void Wire::completeWire(Pin * endPin){
    end = endPin;
    completeFlag = _COMPLETE;
    if (end->type == _OUT)
        logic = end->logic;
    else
        logic = start->logic;
    selectedWireNo = -1;

}

wire_Condtion Wire::getStatus(){
    return(completeFlag);
}


void Wire::removeWire(){
    *this = deadWire;
    // start->type = _BLANKE;
    // end->type = _BLANKE;
    // completeFlag = _ISBLANK;
    // logic = -1;
    selectedWireNo = -1;
}

bool Wire::validWire(Pin * endPin){
    int i;
    if (start->type == endPin->type)
        return(false);
    for (i = 0; i< totalWires; i++){
        if (i == index)
            continue;
        if ((start == wires[i].start || start == wires[i].end) && start->type == _IN){
            std::cout<<"TWO INPUTS ON ONE INPUTR"<<std::endl;
            return(false);
        }
        if ((endPin == wires[i].start || endPin == wires[i].end) && endPin->type == _IN){
            std::cout<<"TWO INPUTS ON ONE INPUTR 222"<<std::endl;
            return(false);
        }
    }
    std::cout<<"TRUE";
    return(true);
}

void Wire::removeWiresToComponent(Component * c){
    int i;
    for (i = 0; i < c->getInputNo(); i++)
        if (start == c->getInPinAddress(i) || end == c->getInPinAddress(i)){
            removeWire();
            return;
        }
    if (start == c->getOutPinAddress() || end == c->getOutPinAddress())
        removeWire();
    return;
}

void Wire::setLogic(){

}