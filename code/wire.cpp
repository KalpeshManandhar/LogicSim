#include "wire.h"
#include "component.h"
#include <iostream>


int Wire::totalWires = 0;
int Wire::selectedWireNo = -1;

// data/pointee for a blank wire
Wire deadWire(1);


Wire::Wire(){
    start = new Pin;
    end = new Pin;
    start->pos = new vec2;
    end->pos = new vec2;
    start->logic = new int;
    end->logic =  new int;
    completeFlag = _ISBLANK;
}

// constructor for dead wire
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
        // 1 = RED
        if (*logic == 1)
            SDL_SetRenderDrawColor(renderer, 200, 0 , 0, 255);
        // 0 = WHITE
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, start->pos->x, start->pos->y, end->pos->x, end->pos->y);
}

// set the values of wire to complete it
void Wire::completeWire(Pin * endPin){
    end = endPin;
    completeFlag = _COMPLETE;
    if (end->type == _OUT){
        logic = end->logic;
    }
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
    // in-in and out-out connections are invalid
    if (start->type == endPin->type)
        return(false);

    for (i = 0; i< totalWires; i++){
        // skips comparison with itself
        if (i == index)
            continue;
        // start or end input pin that is already connected to another component is invalid
        // one input cant have two logic values
        if ((start == wires[i].start || start == wires[i].end) && start->type == _IN){
            return(false);
        }
        if ((endPin == wires[i].start || endPin == wires[i].end) && endPin->type == _IN){
            return(false);
        }
    }
    return(true);
}

void Wire::removeWiresToComponent(Component * c){
    int i;
    // checks if the wire is connected to the to-be-deleted component
    for (i = 0; i < c->getInputNo(); i++)
        if (start == c->getInPinAddress(i) || end == c->getInPinAddress(i)){
            removeWire();
            return;
        }
    if (start == c->getOutPinAddress() || end == c->getOutPinAddress())
        removeWire();
    return;
}

// updates the inputs of next component with output of present component
void Wire::sendLogic(){
    if (start->type == _IN)
        *(start->logic) = *(logic);
    else
        *(end->logic) = *(logic);
}