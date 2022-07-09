#pragma once

#include "graphics.h"

#define MAX_INPUTS 2
#define MAX_OUTPUTS 5


struct vec{
    int x,y;
};

enum c_type{
    _AND, _OR, _NOT, _NAND, _NOR, _XOR, _XNOR, _INPUT, _OUTPUT
};

class Button{
    char text[10];
    bool pressedFlag;
    SDL_Rect buttonData;
public:
    void onPressed();
    void draw(SDL_Renderer* renderer);

};

class Component{
    static short componentNo;
    SDL_Rect spriteSrc, spritePos;
    c_type type;
    bool output[MAX_OUTPUTS], input[MAX_INPUTS];
    Component *next[MAX_OUTPUTS];
public:
    Component();
    ~Component();
    void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    void setValues(c_type type);


};