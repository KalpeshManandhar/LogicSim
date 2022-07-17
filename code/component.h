#pragma once

#include "graphics.h"

#define MAX_INPUTS 2
#define MAX_OUTPUTS 5
#define MAX_COMPONENTS 25


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
    SDL_Rect spriteSrc, compPos;
    c_type type;
    bool output[MAX_OUTPUTS], input[MAX_INPUTS];
    Component *next[MAX_OUTPUTS];
    short index;
public:
    static short componentNo;           // total no of components added init 0
    static short selectedCompNo;        // currently selected component index init -1

    Component();
    ~Component();
    void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    void setValues(c_type type, vec2 &mousePos);
    bool mouseHover(vec2 &mousePos);
    inline void selectComponent();
    void updateSelectedComp(vec2 &mousePos, vec2 &prev);
    


};

extern Component components[MAX_COMPONENTS];
