#include "component.h"
#include "SDL.h"


Component::Component(){
    spriteSrc.h = 72;
    spriteSrc.w = 146;
    spritePos.h = 72;
    spritePos.w = 146;
}

void Component::setValues(c_type type){
    this->type = type;
    if (type < 5){
        spriteSrc.y = 0;
    }
    else{
        spriteSrc.y = 72;
    }
    spriteSrc.x = (type%5) * 146; 
    this->next[0] = NULL;
}


void Component::draw(SDL_Renderer* renderer, SDL_Texture* spritesheet){
    SDL_RenderCopy(renderer, spritesheet, &spriteSrc, &spritePos);
}