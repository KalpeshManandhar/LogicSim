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
    int i = (buttonKey == 1)?0:1;
    static short clickedFrameNo[2] = {0,0};
    // clickedFrameNo[0] for left clicks
    // clickedFrameNo[1] for right clicks

    if ((mouseButtons & SDL_BUTTON(buttonKey))!=0){
        clickedFrameNo[i]++;
        if (clickedFrameNo[i] > 1){
            held = true;
            return(HELD);
        }
        if (clickedFrameNo[i] == 1)
            return(CLICKED);
    }
    
    if (clickedFrameNo[i]>0){
        clickedFrameNo[i] = 0;
        held = false;
        return(RELEASED);
    }
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




void Input::handleMouseInput(vec2 windowSize){
    bool mouseHoverFlag = false;
    int pinHoverFlag = -1;
    static vec2 bounds;
    bounds.x = X_BOUND(windowSize.x);
    bounds.y = Y_BOUND(windowSize.y);
    switch (isPressed(SDL_BUTTON_LEFT))
    {
    case CLICKED:{
        std::cout<<"leftCLick";
        int i;
        // adds a new component
        if (mousePos.y>(bounds.y-50) && mousePos.y<(windowSize.y) && Component::componentNo != MAX_COMPONENTS)
        {
            if(mousePos.y < bounds.y - 10){
                if (mousePos.x>30+0*(130) && mousePos.x<1*130){
                    addComponent(_AND);
                    break;
                }
                if (mousePos.x>30+1*130 && mousePos.x<2*130){
                    addComponent(_OR);
                    break;
                }
                if (mousePos.x>30+2*130 && mousePos.x<3*130){
                    addComponent(_NOT);
                    break;
                }
                if (mousePos.x>30+3*130 && mousePos.x<4*130){
                    addComponent(_NAND);
                    break;
                }
                if (mousePos.x>30+4*130 && mousePos.x<5*130){
                    addComponent(_NOR);
                    break;
                }
                if (mousePos.x>30+5*130 && mousePos.x<6*130){
                    addComponent(_XOR);
                    break;
                }
                if (mousePos.x>30+6*130 && mousePos.x<7*130){
                    addComponent(_XNOR);
                    break;
                }
                if (mousePos.x>30+7*130 && mousePos.x<8*130){
                    addComponent(_INPUT);
                    break;
                }
                if (mousePos.x>30+8*130 && mousePos.x<9*130){
                    addComponent(_OUTPUT);
                    break;
                }
            }
            else{
                if (mousePos.x>30+0*130 && mousePos.x<1*130){
                    addComponent(_ADDER);
                    break;
                }
                if (mousePos.x>30+1*130 && mousePos.x<2*130){
                    addComponent(_SUBTRACTOR);
                    break;
                }
                if (mousePos.x>30+2*130 && mousePos.x<3*130){
                    addComponent(_4x2ENCODER);
                    break;
                }
                if (mousePos.x>30+3*130 && mousePos.x<4*130){
                    addComponent(_2x4DECODER);
                    break;
                }
                if (mousePos.x>30+4*130 && mousePos.x<5*130){
                    addComponent(_NOR);
                    break;
                }
                if (mousePos.x>30+5*130 && mousePos.x<6*130){
                    addComponent(_XOR);
                    break;
                }
                if (mousePos.x>30+6*130 && mousePos.x<7*130){
                    addComponent(_XNOR);
                    break;
                }
                if (mousePos.x>30+7*130 && mousePos.x<8*130){
                    addComponent(_INPUT);
                    break;
                }
                if (mousePos.x>30+8*130 && mousePos.x<9*130){
                    addComponent(_OUTPUT);
                    break;
                }
            }
        }
        
        // selecting a component
        for(i=0;i<Component::componentNo; i++){
            if (components[i]->mouseHover(mousePos, pinHoverFlag) == true){
                components[i]->selectComponent();
                mouseHoverFlag = true;
                break;
            }
        }

        // pin clicked?
        if (pinHoverFlag == 1){
            std::cout<<"Pin clicked";
            if (Component::selectedPin->type == _IN)
                std::cout<<"Input";
            else
                std::cout<<"output";

            // adds wire if no wire is currently selected (start pin)
            if (Wire::selectedWireNo == -1)
                addWire();

            // checks if the wire is valid (end pin)
            else{
                if (wires[Wire::selectedWireNo].validWire(Component::selectedPin))
                    wires[Wire::selectedWireNo].completeWire(Component::selectedPin);
                else
                    wires[Wire::selectedWireNo].removeWire();
            }
        }
        // adds anchor points for wire if clicked on empty space
        else{
            if (Wire::selectedWireNo != -1){
                wires[Wire::selectedWireNo].addVertex(mousePos);
            }
        }

        // unselects component if clicked outside components
        if (mouseHoverFlag == false){
            Component::selectedCompNo = -1;     
        }
        break;
    }

    // updates the position of component if selected
    case HELD:{
        std::cout<<"leftHELD"<<std::endl;
        if (Component::selectedCompNo != -1){
            components[Component::selectedCompNo]->updateSelectedComp(mousePos, prevMousePos);
        }
        break;
    }

    case RELEASED:{
        std::cout<<"leftRELEASED"<<std::endl;
        if ((mousePos.x > X_BOUND(windowSize.x) || mousePos.y > Y_BOUND(windowSize.y)) && Component::selectedCompNo != -1){
            int i;
            // removes the wires associated with the component
            for (i = 0; i < Wire::totalWires; i++)
                wires[i].removeWiresToComponent(components[Component::selectedCompNo]);
            // removes the component
            components[Component::selectedCompNo]->removeComponent();
        }
        break;
    }

    case PRESSED:
    case IDLE:
    default:
        break;
    }
    
    // removes wire on right mouse click
    if (isPressed(SDL_BUTTON_RIGHT) == CLICKED && Wire::selectedWireNo != -1){
        wires[Wire::selectedWireNo].removeWire();
    }
}


void Input::addComponent(c_type type){
    int availableIndex = -1,i;
    // checks if any previous index is free due to deleted components
    for (i=0;i<Component::componentNo;i++){
        if (components[i]->getType() == _NOTHING){
            availableIndex = i;
            break;
        }
    }
    if (type == _INPUT){
        std::cout<<"Added input comp";
        if (availableIndex == -1){
            components[Component::componentNo] = new InputComponent;
            components[Component::componentNo]->setValues(type, mousePos,-1);
        }
        else{
            delete components[availableIndex];
            components[availableIndex] = new InputComponent;
            components[availableIndex]->setValues(type, mousePos, availableIndex);
        }
    }
    else if (type == _OUTPUT){
        std::cout<<"Added output comp";
        if (availableIndex == -1){
            components[Component::componentNo] = new OutputComponent;
            components[Component::componentNo]->setValues(type, mousePos,-1);
        }
        else{
            delete components[availableIndex];
            components[availableIndex] = new OutputComponent;
            components[availableIndex]->setValues(type, mousePos, availableIndex);
        }
    }
    else{
        if (availableIndex == -1){
            components[Component::componentNo] = new Component;
            components[Component::componentNo]->setValues(type, mousePos,-1);
        }
        else{
            delete components[availableIndex];
            components[availableIndex] = new Component;
            components[availableIndex]->setValues(type, mousePos, availableIndex);
        }
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







