#include "component.h"
#include "SDL.h"
#include <iostream>


short Component::componentNo = 0;
short Component::selectedCompNo = -1;

Component::Component(){
    spriteSrc.h = 72;
    spriteSrc.w = 146;
    compPos.h = 72;
    compPos.w = 146;
    spriteSrc.y = 216;
    spriteSrc.x = 0;
    compPos.x = -200;
    compPos.y = -200;
}

Component::~Component(){
    spriteSrc.y = 216;
    spriteSrc.x = 0;
    compPos.x = -200;
    compPos.y = -200;
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
        outPinPos.x = -200;
        outPinPos.y = -400;       
    }
    // one output pin
    else{
        outPinPos.x = 141;
        outPinPos.y = 35;
    }
    
    // only one input pin
    if (type == _NOT || type == _OUTPUT){           
        inPinPos[0].x = 4;
        inPinPos[0].y = 36;
    }
    // zero input pins
    else if (type == _INPUT){                       
        inPinPos[0].x = -200;
        inPinPos[0].y = -400;
    }
    // two input pins
    else{                                           
        inPinPos[0].x = 4;
        inPinPos[0].y = 18;
        inPinPos[1].x = 4;
        inPinPos[1].y = 52;
    }

}


void Component::draw(SDL_Renderer* renderer, SDL_Texture* spritesheet){
    SDL_RenderCopy(renderer, spritesheet, &spriteSrc, &compPos);
}


bool Component::mouseHover(vec2 &mousePos){
    if ((mousePos.x > compPos.x) && (mousePos.x < (compPos.x + compPos.w)) && (mousePos.y > compPos.y) && (mousePos.y < (compPos.y + compPos.h))){
        return(true);
    }
    return(false);
}

void Component::selectComponent(){
    selectedCompNo = index;
}

void Component::updateSelectedComp(vec2 &mousePos, vec2 &prev){
    compPos.x += (mousePos.x - prev.x);
    compPos.y += (mousePos.y - prev.y);
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