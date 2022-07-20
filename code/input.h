#pragma once
#include "utils.h"
#include <SDL.h>
#include "component.h"

enum b_States{
    PRESSED, HELD, RELEASED, IDLE, CLICKED
};



class Input{
    SDL_Event event;    
    Uint32 mouseButtons;
    bool held;
public:
    vec2 mousePos, prevMousePos;
    b_States isPressed(int buttonKey);
    void getMouseState();
    int pollEvents();
    void printMousePos();
    void handleMouseInput();
    void addComponent(c_type type);
    

};