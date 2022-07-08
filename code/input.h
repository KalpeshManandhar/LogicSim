#pragma once
#include <SDL.h>

struct vec2{        // 2d vector for coordinates 
    int x,y;
};


class Input{
    SDL_Event event;
    vec2 mousePos;
    Uint32 mouseButtons;
    bool isHeld;
public:
    bool isPressed(int buttonKey);
    void getMouseState();
    int pollEvents();
    void printMousePos();

};