#include "input.h"
#include <iostream>

// gets state of mouse buttons and position of cursor
void Input::getMouseState(){
    mouseButtons = SDL_GetMouseState(&mousePos.x, &mousePos.y);
}

// checks if a given mouse button is pressed or not
bool Input::isPressed(int buttonKey){  
    static short clickedFrameNo = 0;
    if (mouseButtons && SDL_BUTTON(buttonKey)!=0){
        if (clickedFrameNo> 10)
            held = true;
        return(true);
    }
    if (clickedFrameNo > 10){
        std::cout<<"Held"<<std::endl;
    }
    else if (clickedFrameNo > 0){
        std::cout<<"Pressed"<<std::endl;
    }
    clickedFrameNo = 0;
    held = false;
    // clickedFrameNo[0] = 0;              // for left
    // clickedFrameNo[1] = 0;              // for right
    return(false);
}

bool Input::isHeld(int buttonKey){
    


}

// gets the events for the window
int Input::pollEvents(){
    SDL_PollEvent(&event);
    return(event.type);
}

void Input::printMousePos(){
    std::cout<<mousePos.x<<" , "<<mousePos.y<<std::endl;
}