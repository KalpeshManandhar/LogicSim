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
    vec2 vertices[6];
    int *logic;                      // logic in the wire
    wire_Condtion completeFlag;     // if the wire is connected fully or not
    int index, verticesNo;
public:
    static int totalWires;
    static int selectedWireNo;

    Wire();
    Wire(int def);
    ~Wire();
    void addWire(Pin *startPin, vec2 *endPoint, int availableIndex);
    void draw(SDL_Renderer *renderer);
    bool validWire(Pin * endPin);
    void completeWire(Pin * endPin);
    void addVertex(vec2 vertex);
    void sendLogic();
    void removeWire();
    void removeWiresToComponent(Component * c);

    wire_Condtion getStatus();
};


extern Wire *wires;
