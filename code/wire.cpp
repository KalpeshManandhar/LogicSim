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
    // start->pos = NULL;
    // end->pos = NULL;
    completeFlag = _ISBLANK;
    logic = -1;
}

Wire::Wire(int def){
    start = new Pin;
    end = new Pin;
    start->pos = new vec2;
    end->pos = new vec2;
    start->pos->x = -200;
    start->pos->y = -200;
    end->pos->x = -200;
    end->pos->y = -200;

    completeFlag = _ISBLANK;
    logic = -1;
}

Wire::~Wire(){

}


void Wire::addWire(Pin *startPin, vec2 *endPoint, int availableIndex){
    std::cout<<"Added wisdsdre "<<index<<std::endl;

    if (availableIndex == -1){
        index = totalWires;
        totalWires++;
    }
    else{
        index = availableIndex;
    }
    selectedWireNo = index;
    std::cout<<"Added wisdsdre "<<index<<std::endl;


    start = startPin;
    end->pos = endPoint;
    completeFlag = _INCOMPLETE;
    std::cout<<"Added wire "<<index<<std::endl;
    std::cout<<start->pos->x<<","<<start->pos->y<<std::endl;
}



void Wire::draw(SDL_Renderer * renderer){
    if (logic == 1)
        SDL_SetRenderDrawColor(renderer, 200, 0 , 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // if (completeFlag == _INCOMPLETE)
    //     SDL_RenderDrawLine(renderer, start->x, start->y, end.x, end.y);
    // else
    SDL_RenderDrawLine(renderer, start->pos->x, start->pos->y, end->pos->x, end->pos->y);
}


void Wire::completeWire(Pin * endPin){
    end = endPin;
    completeFlag = _COMPLETE;
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
        if ((start == wires[i].start || start == wires[i].end) && start->type == _IN)
            return(false);
        if ((endPin == wires[i].start || endPin == wires[i].end) && endPin->type == _IN)
            return(false);
        
    }
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