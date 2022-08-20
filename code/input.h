#pragma once
#include "utils.h"
#include "component.h"
#include "wire.h"
#include <SDL.h>


enum b_States{
    PRESSED, HELD, RELEASED, IDLE, CLICKED
};



class Input{
    SDL_Event event;    
    Uint32 mouseButtons;
    const unsigned char *keyStates;
public:
    vec2 mousePos, prevMousePos;
    b_States isPressed(int buttonKey);
    b_States isKeyPressed(SDL_Scancode keyCode);
    void getMouseState();
    int pollEvents();
    void printMousePos();
    void handleMouseInput(vec2 windowSize, load_type & type);
    void addWire();
    void addComponent(c_type type);
    void getKeyboardState();
    void handleKeyInput();
};