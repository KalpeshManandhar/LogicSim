#include "component.h"
#include "SDL.h"
#include <iostream>


short Component::componentNo = 0;
short Component::selectedCompNo = -1;
Pin* Component::selectedPin = NULL;

// int InputComponent::totaliProbes = 0;
// int InputComponent::selectedIprobe = -1;


Component::Component(){
    spriteSrc.h = 72;
    spriteSrc.w = 146;
    compPos.h = 72;
    compPos.w = 146;
    spriteSrc.y = 216;
    spriteSrc.x = 0;
    compPos.x = -200;
    compPos.y = -200;
    int i;
    for (i = 0; i<MAX_INPUTS; i++)
        inPin[i].pos = new vec2;
    outPin.pos = new vec2;
}

Component::~Component(){

}

void Component::setValues(c_type type, vec2 &mousePos, int availableIndex){
    // sets the type of component
    this->type = type;

    setSprites();
    setInputNo();
    setPinPos();

    // sets the index of the array where the component is to be stored
    if (availableIndex == -1){
        index = componentNo;
        componentNo++;
    }
    else{
        index = availableIndex;
    }
    selectedCompNo = index;

    // sets the spawn position of the component
    compPos.x = mousePos.x - compPos.w * 0.5;
    compPos.y = mousePos.y - compPos.h * 0.3;

    // sets the spawn positions and data of the pins
    int  i;
    for (i = 0; i<inputNo; i++){
        inPin[i].pos->x  += compPos.x;
        inPin[i].pos->y  += compPos.y;
        inPin[i].type = _IN;
        input[i] = -1;
        inPin[i].logic = &input[i];
    }
    outPin.pos->x  += compPos.x;
    outPin.pos->y  += compPos.y;
    outPin.type = _OUT;
    output = -1;
    outPin.logic = &output;

    output = 1;

    std::cout<<"COmp added"<<index<<std::endl;
}


void Component::setSprites(){
    if (type < 5){
        spriteSrc.y = 0;
    }
    else{
        spriteSrc.y = 72;
    }
    spriteSrc.x = (type%5) * 146; 
}

void Component::setInputNo(){
    switch (type)
    {
    case _NOT:
    case _OUTPUT:
        inputNo = 1;
        break;
    case _INPUT:
        inputNo = 0;
        break;
    case _AND:
    case _OR:
    case _NAND:
    case _NOR:
    case _XOR:
    case _XNOR:
        inputNo = 2;
        break;
    default:
        break;
    }

}

void Component::setPinPos(){
    // zero output pins
    if (type == _OUTPUT){               
        outPin.pos->x = -200;
        outPin.pos->y = -400;       
    }
    // one output pin
    else{
        outPin.pos->x = 141;
        outPin.pos->y = 35;
    }
    
    // only one input pin
    if (type == _NOT || type == _OUTPUT){           
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 36;
    }
    // zero input pins
    else if (type == _INPUT){                       
        inPin[0].pos->x = -200;
        inPin[0].pos->y = -400;
    }
    // two input pins
    else{                                           
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 18;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 52;
    }

}


void Component::draw(SDL_Renderer* renderer, SDL_Texture* spritesheet){
    SDL_RenderCopy(renderer, spritesheet, &spriteSrc, &compPos);
}



// returns true if mouse is hovering over a component and also sets the value of pinHover to true if the mouse is hovering over a pin
bool Component::mouseHover(vec2 &mousePos, int & pinHover){
    int i;
    if ((mousePos.x > compPos.x) && (mousePos.x < (compPos.x + compPos.w)) && (mousePos.y > compPos.y) && (mousePos.y < (compPos.y + compPos.h))){

        // hovering over an input pin?
        for (i = 0; i<inputNo; i++){
            if ((mousePos.x > inPin[i].pos->x - 10) && (mousePos.x < inPin[i].pos->x +10) && (mousePos.y > inPin[i].pos->y - 10) && (mousePos.y < inPin[i].pos->y +10)){
                pinHover = 1;
                selectedPin = &inPin[i];
                return(true);
            }
        }
        // hovering over an output pin?
        if ((mousePos.x > outPin.pos->x - 10) && (mousePos.x < outPin.pos->x +10) && (mousePos.y > outPin.pos->y - 10) && (mousePos.y < outPin.pos->y +10)){
            pinHover = 1;
            selectedPin = &outPin;
        }
        return(true);
    }
    pinHover = 0;
    return(false);
}

void Component::selectComponent(){
    selectedCompNo = index;
}

void Component::updateSelectedComp(vec2 &mousePos, vec2 &prev){
    compPos.x += (mousePos.x - prev.x);
    compPos.y += (mousePos.y - prev.y);

    // updates position of the pins
    int i;
    for (i = 0; i<inputNo; i++){
        inPin[i].pos->x  += (mousePos.x - prev.x);
        inPin[i].pos->y  += (mousePos.y - prev.y);
    }
    outPin.pos->x  += (mousePos.x - prev.x);
    outPin.pos->y  += (mousePos.y - prev.y);
}

void Component::removeComponent(){
    spriteSrc.y = 216;
    spriteSrc.x = 0;
    compPos.x = -200;
    compPos.y = -200;
    type = _NOTHING;
    selectedCompNo = -1;
    std::cout<<"Removed comp"<<index<<std::endl;
}


c_type Component::getType(){
    return(type);
}

int Component::getInputNo(){
    return(inputNo);
}

Pin * Component::getInPinAddress(int i){
    return(&inPin[i]);
}

Pin* Component::getOutPinAddress(){
    return(&outPin);
}

InputComponent::InputComponent(){

}

void InputComponent::setButtonPos(){
    inputButton.button.x = 80;
    inputButton.button.y = 15;
    inputButton.button.w = 40;
    inputButton.button.h = 40;
}

void InputComponent::onPressed(){
    output = (output == 1)?0:1;
}

void InputComponent::updateSelectedComp(vec2 &mousePos, vec2 &prev){
    Component::updateSelectedComp(mousePos, prev);
    inputButton.button.x += (mousePos.x - prev.x);
    inputButton.button.y += (mousePos.y - prev.y);
}

void InputComponent::setValues(c_type type, vec2 &mousePos, int availableIndex){
    std::cout<<"Set value";
    Component::setValues(type, mousePos, availableIndex);
    setButtonPos();
    inputButton.button.x += compPos.x;
    inputButton.button.y += compPos.y;
}

void InputComponent::draw(SDL_Renderer* renderer, SDL_Texture* spritesheet){
    SDL_RenderCopy(renderer, spritesheet, &spriteSrc, &compPos);
    // std::cout<<"DRAW";
    if (output == 1)
        SDL_SetRenderDrawColor(renderer, 200, 0, 0,255);
    else 
        SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    SDL_RenderFillRect(renderer, &inputButton.button);
}

bool InputComponent::mouseHover(vec2 &mousePos, int & pinHover){
    if ((mousePos.x > compPos.x) && (mousePos.x < (compPos.x + compPos.w)) && (mousePos.y > compPos.y) && (mousePos.y < (compPos.y + compPos.h))){
        if ((mousePos.x > inputButton.button.x) && (mousePos.x < (inputButton.button.x + inputButton.button.w)) && (mousePos.y > inputButton.button.y) && (mousePos.y < inputButton.button.y + inputButton.button.h)){
            onPressed();
        }
    } 
    return(Component::mouseHover(mousePos, pinHover));
}

int * Component::getInputs(){
    return(input);
}

void Component::setOutput(int op){
    output = op;
}