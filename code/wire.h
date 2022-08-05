#pragma once

#include "utils.h"
#include "component.h"
#include "SDL.h"

#define MAX_WIRES 50

enum wire_Condtion{
    _COMPLETE, _INCOMPLETE, _ISBLANK 
};


class Wire{
    Pin *start, *end;
    int *logic;                      // logic in the wire
    wire_Condtion completeFlag;     // if the wire is connected fully or not
    int index;
public:
    static int totalWires;
    static int selectedWireNo;

    Wire();
    Wire(int def);
    ~Wire();
    void addWire(Pin *startPin, vec2 *endPoint, int availableIndex);
    void draw(SDL_Renderer *renderer);
    void completeWire(Pin * endPin);
    void removeWire();
    void removeWiresToComponent(Component * c);
    bool validWire(Pin * endPin);
    void setLogic();

    wire_Condtion getStatus();
};


extern Wire *wires;
