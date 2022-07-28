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
    int pinHoverFlag = -1;
    switch (isPressed(SDL_BUTTON_LEFT))
    {
    case CLICKED:{
        std::cout<<"CLick";
        int i;
        // adds a new component
        // if (mousePos.y>Y_BOUND){
        //     addComponent();
            
        //     break;
        // }
        if (mousePos.y>620 && mousePos.y<670 && Component::componentNo != MAX_COMPONENTS)
        {
            if (mousePos.x>50+0*146 && mousePos.x<50+(0+1)*100){
                addComponent(_AND);
                
                break;
            }
            if (mousePos.x>50+1*146 && mousePos.x<150+1*146){
                addComponent(_OR);
                
                break;
            }
            if (mousePos.x>50+2*146 && mousePos.x<150+2*146){
                addComponent(_NOT);
                
                break;
            }
            if (mousePos.x>50+3*146 && mousePos.x<150+3*146){
                addComponent(_NAND);
                
                break;
            }
            if (mousePos.x>50+4*146 && mousePos.x<150+4*146){
                addComponent(_NOR);
                
                break;
            }
        }
        

        for(i=0;i<Component::componentNo; i++){
            if (components[i].mouseHover(mousePos, pinHoverFlag) == true){
                components[i].selectComponent();
                mouseHoverFlag = true;
                break;
            }
        }

        if (pinHoverFlag == 1){
            std::cout<<"Pin clicked";
            if (Component::selectedPin->type == _IN)
                std::cout<<"Input";
            else
                std::cout<<"output";

            // adds wire
            if (Wire::selectedWireNo == -1)
                addWire();
            else{
                if (wires[Wire::selectedWireNo].validWire(Component::selectedPin))
                    wires[Wire::selectedWireNo].completeWire(Component::selectedPin);
                else
                    wires[Wire::selectedWireNo].removeWire();
            }
        }
        // unselects/ removes wire when clicked outside component
        // else{
        //     if (Wire::selectedWireNo != -1)
        //         Wire::selectedWireNo == -1;
        //     else{
        //         wires[Wire::selectedWireNo].removeWire();
        //     }
        // }



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
            int i;
            // to remove the wires associated with the component
            for (i = 0; i < Wire::totalWires; i++)
                wires[i].removeWiresToComponent(components[Component::selectedCompNo]);
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
    //         if (components[i]->mouseHover(mousePos) == true){
    //             components[i]->selectComponent();
    //         }
    //     }
    // }


}


void Input::addComponent(c_type type){
    int availableIndex = -1,i;
    // checks if any previous index is free due to deleted components
    for (i=0;i<Component::componentNo;i++){
        if (components[i].getType() == _NOTHING){
            availableIndex = i;
            break;
        }
    }
    if (availableIndex == -1){
        components[Component::componentNo].setValues(type, mousePos,-1);
    }
    else{
        components[availableIndex].setValues(type, mousePos, availableIndex);
    }
}

void Input::addWire(){
    int availableIndex = -1,i;
    // checks if any previous index is free due to deleted wires
    for (i=0;i<Wire::totalWires;i++){
        if (wires[i].getStatus() == _ISBLANK){
            availableIndex = i;
            break;
        }
    }
    if (availableIndex == -1){
        wires[Wire::totalWires].addWire(Component::selectedPin, &mousePos, -1);
    }
    else{
        wires[availableIndex].addWire(Component::selectedPin, &mousePos, availableIndex);
    }
}







