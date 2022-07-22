#include "input.h"
#include "component.h"
#include <iostream>



// gets state of mouse buttons and position of cursor
void Input::getMouseState(){
    prevMousePos = mousePos;
    mouseButtons = SDL_GetMouseState(&mousePos.x, &mousePos.y);
}

// checks if a given mouse button is pressed or not
b_States Input::isPressed(int buttonKey){  
    static short clickedFrameNo = 0;
    if (mouseButtons && SDL_BUTTON(buttonKey)!=0){
        clickedFrameNo++;
        if (clickedFrameNo > 1){
            held = true;
            return(HELD);
        }
        if (clickedFrameNo == 1)
            return(CLICKED);
        return(PRESSED);
    }
    
    if (clickedFrameNo>0){
        clickedFrameNo = 0;
        held = false;
        return(RELEASED);
    }
    // clickedFrameNo[0] = 0;              // for left
    // clickedFrameNo[1] = 0;              // for right
    return(IDLE);
}


// gets the events for the window
int Input::pollEvents(){
    SDL_PollEvent(&event);
    return(event.type);
}

void Input::printMousePos(){
    std::cout<<mousePos.x<<" , "<<mousePos.y<<std::endl;
}

void Input::handleMouseInput(){
    bool mouseHoverFlag = false;
    switch (isPressed(SDL_BUTTON_LEFT))
    {
    case CLICKED:{
        std::cout<<"CLick";
        int i;
        // adds a new component
        if (mousePos.y>Y_BOUND && Component::componentNo != MAX_COMPONENTS){
            addComponent();
            
            break;
        }

        for(i=0;i<Component::componentNo; i++){
            if (components[i].mouseHover(mousePos) == true){
                components[i].selectComponent();
                mouseHoverFlag = true;
                break;
            }
        }
        // unselects component if clicked outside components
        if (mouseHoverFlag == false){
            Component::selectedCompNo = -1;     
        }
        break;
    }
    case PRESSED:{

        break;
    }

    // updates the position of component if selected
    case HELD:{
        std::cout<<"HELD"<<std::endl;
        if (Component::selectedCompNo != -1){
            components[Component::selectedCompNo].updateSelectedComp(mousePos, prevMousePos);
        }
        break;
    }
    case RELEASED:{
        std::cout<<"RELEASED"<<std::endl;
        if ((mousePos.x > X_BOUND || mousePos.y > Y_BOUND) && Component::selectedCompNo != -1){
            components[Component::selectedCompNo].removeComponent();
        }
        break;
    }
    case IDLE:{

        break;
    }
    default:
        break;
    }
    // if (isPressed(SDL_BUTTON_LEFT)==CLICKED){
    //     int i;
    //     for(i=0;i<Component::componentNo;i++){
    //         if (components[i].mouseHover(mousePos) == true){
    //             components[i].selectComponent();
    //         }
    //     }
    // }


}


void Input::addComponent(){
    int availableIndex = -1,i;
    // checks if any previous index is free due to deleted components
    for (i=0;i<Component::componentNo;i++){
        if (components[i].getType() == _NOTHING){
            availableIndex = i;
            break;
        }
    }
    if (availableIndex == -1){
        components[Component::componentNo].setValues(_AND, mousePos,-1);
    }
    else{
        components[availableIndex].setValues(_AND, mousePos, availableIndex);
    }
}

