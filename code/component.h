#pragma once

#include "utils.h"
#include "SDL.h"
#include "logic.h"

#define MAX_INPUTS 2
#define MAX_OUTPUTS 5
#define MAX_COMPONENTS 25
#define MAX_PROBES 5

#define Y_BOUND 680
#define X_BOUND 1200



struct Button{
    SDL_Rect button;
    bool pressedFlag;
};


class Component{
protected:
    SDL_Rect spriteSrc, compPos;
    c_type type;
    int inputNo;                                    // no of inputs for each component
    int output, input[MAX_INPUTS];
    Component *next[MAX_OUTPUTS];
    short index;                                    // index in the array
    Pin inPin[MAX_INPUTS], outPin;                  // only one output + different number of inputs for different components

public:
    static short componentNo;                       // total no of components added init 0
    static short selectedCompNo;                    // currently selected component index init -1
    static Pin* selectedPin;

    Component();
    ~Component();
    void setSprites();
    void setInputNo();
    void setPinPos();

    virtual void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    virtual void setValues(c_type type, vec2 &mousePos, int availableIndex);
    virtual bool mouseHover(vec2 &mousePos, int & pinHover);
    virtual void updateSelectedComp(vec2 &mousePos, vec2 &prev);

    void selectComponent();
    void removeComponent();
    void setOutput(int op);

    c_type getType();
    int getInputNo();
    Pin* getInPinAddress(int i);
    Pin* getOutPinAddress();
    int * getInputs();

    friend class Logic;
};


class InputComponent:public Component{
    Button inputButton;
public:

    InputComponent();
    void setButtonPos();
    void setValues(c_type type,vec2 &mousePos, int availableIndex );
    void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    void updateSelectedComp(vec2 &mousePos, vec2 &prev);
    void onPressed();
    bool mouseHover(vec2 &mousePos, int & pinHover);
    

};


extern Component *components[MAX_COMPONENTS];


