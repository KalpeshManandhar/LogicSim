#include "input.h"
#include <iostream>

// gets state of mouse buttons and position of cursor
void Input::getMouseState(){
    mouseButtons = SDL_GetMouseState(&mousePos.x, &mousePos.y);
}

// checks if a given mouse button is pressed or not
bool Input::isPressed(int buttonKey){    
    if (mouseButtons && SDL_BUTTON(buttonKey)!=0)
        return(true);
    return(false);
}

// gets the events for the window
int Input::pollEvents(){
    SDL_PollEvent(&event);
    return(event.type);
}

void Input::printMousePos(){
    std::cout<<mousePos.x<<" , "<<mousePos.y<<std::endl;
}