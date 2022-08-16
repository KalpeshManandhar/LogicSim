#pragma once

#include "utils.h"
#include "SDL.h"

#define MAX_INPUTS 5
#define MAX_OUTPUTS 5
#define MAX_COMPONENTS 25
#define MAX_PROBES 5

#define Y_BOUND(Y) (Y - 60)
#define X_BOUND(X) (X - 80)



struct Button{
    SDL_Rect button;
    bool pressedFlag;
    bool mouseHover(vec2 mousePos){
        if ((mousePos.x > button.x) && (mousePos.x < (button.x + button.w)) && (mousePos.y > button.y) && (mousePos.y < button.y + button.h)){
            return(true);
        }   
        return(false);
    }
};


class Component{
protected:
    SDL_Rect spriteSrc, compPos;
    c_type type;
    short index;                                    // index in the array
    int inputNo, outputNo;                          // no of inputs/ outputs for each component
    int output[MAX_OUTPUTS], input[MAX_INPUTS];
    Pin inPin[MAX_INPUTS], outPin[MAX_OUTPUTS];     // only one output + different number of inputs for different components
    bool sendOp;
public:
    static short componentNo;                       // total no of components added init 0
    static short selectedCompNo;                    // currently selected component index init -1
    static Pin* selectedPin;

    Component();
    virtual ~Component();
    void setSprites();
    void setPinNo();
    void setPinPos();

    virtual void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    virtual void setValues(c_type type, vec2 &mousePos, int availableIndex);
    virtual bool mouseHover(vec2 &mousePos, int & pinHover);
    virtual void updateSelectedComp(vec2 &mousePos, vec2 &prev);
    virtual void setOutput(int op);

    void selectComponent();
    void removeComponent();

    c_type getType();
    int getInputNo();
    int getOutputNo();
    Pin* getInPinAddress(int i);
    Pin* getOutPinAddress(int i);
    int * getInputs();
    bool sendOutput();
};


class InputComponent:public Component{
    Button inputButton;
public:
    void setButtonPos();
    virtual void onPressed();

    void setValues(c_type type,vec2 &mousePos, int availableIndex );
    void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    void updateSelectedComp(vec2 &mousePos, vec2 &prev);
    bool mouseHover(vec2 &mousePos, int & pinHover);
};


class OutputComponent:public Component{
    SDL_Rect display;
public:
    void setDisplayPos();
    void setValues(c_type type,vec2 &mousePos, int availableIndex );
    void draw(SDL_Renderer* renderer, SDL_Texture* spritesheet);
    void updateSelectedComp(vec2 &mousePos, vec2 &prev);
};

class Clock:public InputComponent{
    float duration;
    float T;
    bool logicToSend;
public:
    Clock(float timePeriod);
    void setOutput(int frameTime);
};



extern Component *components[MAX_COMPONENTS];


