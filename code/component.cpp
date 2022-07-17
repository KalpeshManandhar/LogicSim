#include "component.h"
#include "utils.h"
#include "SDL.h"

#define Y_BOUND 680
#define X_BOUND 1280

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

void Component::setValues(c_type type, vec2 &mousePos){
    this->type = type;
    if (type < 5){
        spriteSrc.y = 0;
    }
    else{
        spriteSrc.y = 72;
    }
    spriteSrc.x = (type%5) * 146; 
    // this->next[0] = NULL;

    index = componentNo;
    selectedCompNo = index;
    compPos.x = mousePos.x - compPos.w * 0.5;
    compPos.y = mousePos.y - compPos.h * 0.3;
    Component::componentNo++;
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

inline void Component::selectComponent(){
    selectedCompNo = index;
}

void Component::updateSelectedComp(vec2 &mousePos, vec2 &prev){
    compPos.x += (mousePos.x - prev.x);
    compPos.y += (mousePos.y - prev.y);
}