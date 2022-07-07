#pragma once

#include "SDL2/SDL.h"

struct vec2{
    int x,y;
};


class Input{
    SDL_Event event;
    vec2 mousePos;
    Uint32 mouseButtons;
public:
    bool isPressed(int buttonKey);
    void getMouseState();
    
};