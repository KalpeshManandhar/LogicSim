#pragma once

#include "utils.h"
#include "SDL.h"

#define MAX_WIRES 50

enum wire_Condtion{
    _COMPLETE, _INCOMPLETE, _ISBLANK 
};


class Wire{
    vec2 *start, *end;
    int logic;                      // logic in the wire
    wire_Condtion completeFlag;     // if the wire is connected fully or not
    int index;
public:
    static int totalWires;
    static int selectedWireNo;

    Wire();
    ~Wire();
    void addWire(vec2 *startPoint, vec2 *endPoint, int availableIndex);
    void draw(SDL_Renderer *renderer);
    void completeWire();
    void removeWire();
    wire_Condtion getStatus();
};


extern Wire *wires;