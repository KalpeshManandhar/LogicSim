#pragma once

#include "utils.h"
#include "graphics.h"

#define MAX_INPUTS 2
#define MAX_OUTPUTS 5
#define MAX_COMPONENTS 25

#define Y_BOUND 680
#define X_BOUND 1200


enum c_type{
    _AND, _OR, _NOT, _NAND, _NOR, _XOR, _XNOR, _INPUT, _OUTPUT, _NOTHING
};

class Button{
    bool pressedFlag;
    SDL_Rect buttonData;
public:
    virtual void onPressed();
    void draw(SDL_Renderer* renderer);

};


class Component{
protected:
    SDL_Rect spriteSrc, compPos;
    c_type type;
    int inputNo;                                    // no of inputs for each component
    bool output, input[MAX_INPUTS];
    Component *next[MAX_OUTPUTS];
    short index;                                    // index in the array
    vec2 inPinPos[MAX_INPUTS], outPinPos;           // only one output + different number of inputs for different components

public:
    static short componentNo;                       // total no of components added init 0
    static short selectedCompNo;                    // currently selected component index init -1

    Component();
    ~Component();
    void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    void setValues(c_type type, vec2 &mousePos, int availableIndex );
    void setSprites();
    void setInputNo();
    void setPinPos();
    bool mouseHover(vec2 &mousePos);
    void selectComponent();
    void updateSelectedComp(vec2 &mousePos, vec2 &prev);
    void removeComponent();
    c_type getType();
};


class InputComponent:public Component{
    Button inputChange;
public:
    InputComponent();


};


extern Component components[MAX_COMPONENTS];


