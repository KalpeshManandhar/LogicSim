#pragma once
#include <SDL.h>

struct vec2{        // 2d vector for coordinates 
    int x,y;
};


class Input{
    SDL_Event event;    
    Uint32 mouseButtons;
    bool isHeld;
public:
    vec2 mousePos;
    bool isPressed(int buttonKey);
    void getMouseState();
    int pollEvents();
    void printMousePos();

};