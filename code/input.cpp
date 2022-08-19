#include "input.h"
#include "component.h"
#include <iostream>
//int comp_spawn[13][4];



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
            return(HELD);
        }
        if (clickedFrameNo[i] == 1)
            return(CLICKED);
    }
    
    if (clickedFrameNo[i]>0){
        clickedFrameNo[i] = 0;
        return(RELEASED);
    }
}


// gets the events for the window
int Input::pollEvents(){
    SDL_PollEvent(&event);
    return(event.type);
}

void Input::printMousePos(){
    std::cout<<mousePos.x<<" , "<<mousePos.y<<std::endl;
}




void Input::handleMouseInput(vec2 windowSize, load_type &type){
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
        if (mousePos.y>(bounds.y-50) && mousePos.y<(windowSize.y) && Component::componentNo != MAX_COMPONENTS){
            if(type == _GATES){
                if(mousePos.y>comp_spawn[0][1] && mousePos.y<(comp_spawn[0][1]+comp_spawn[0][3])){
                    if (mousePos.x>comp_spawn[0][0] && mousePos.x<(comp_spawn[0][0]+comp_spawn[0][2]) ){
                        addComponent(_AND);
                    }
                    else if (mousePos.x>=comp_spawn[1][0] && mousePos.x<=(comp_spawn[1][2]+comp_spawn[1][0]) ){
                        addComponent(_OR);
                    }
                    else if (mousePos.x>comp_spawn[2][0] && mousePos.x<(comp_spawn[2][2]+comp_spawn[2][0]) ){
                        addComponent(_NOT);
                    }
                    else if (mousePos.x>comp_spawn[3][0] && mousePos.x<(comp_spawn[3][2]+comp_spawn[3][0])){
                        addComponent(_NAND);
                    }
                    else if (mousePos.x>comp_spawn[4][0] && mousePos.x<(comp_spawn[4][2] +comp_spawn[4][0])){
                        addComponent(_NOR);
                    }
                    else if (mousePos.x>comp_spawn[5][0] && mousePos.x<(comp_spawn[5][2] +comp_spawn[5][0])){
                        addComponent(_XOR);
                    }
                    else if (mousePos.x>comp_spawn[6][0] && mousePos.x<(comp_spawn[6][2]+comp_spawn[6][0]) ){
                        addComponent(_XNOR);
                    }
                }
            }
            else if(type == _COMBINATIONAL){
                if (mousePos.x>comp_spawn[0][0] && mousePos.x<(comp_spawn[0][0]+comp_spawn[0][2]) ){
                    addComponent(_ADDER);
                    break;
                }
                else if (mousePos.x>comp_spawn[1][0] && mousePos.x<(comp_spawn[1][0]+comp_spawn[1][2]) ){
                    addComponent(_SUBTRACTOR);
                    break;
                }
                else if (mousePos.x>comp_spawn[2][0] && mousePos.x<(comp_spawn[2][0]+comp_spawn[2][2]) ){
                    addComponent(_4x2ENCODER);
                    break;
                }
                else if (mousePos.x>comp_spawn[3][0] && mousePos.x<(comp_spawn[3][0]+comp_spawn[3][2]) ){
                    addComponent(_2x4DECODER);
                    break;
                }
                else if (mousePos.x>comp_spawn[4][0] && mousePos.x<(comp_spawn[4][0]+comp_spawn[4][2]) ){
                    addComponent(_8x1MUX);
                    break;
                }
                else if (mousePos.x>comp_spawn[5][0] && mousePos.x<(comp_spawn[5][0]+comp_spawn[5][2]) ){
                    addComponent(_1x8DEMUX);
                    break;
                }
            }
            else if(type == _SEQUENTIAL){
                if (mousePos.x>comp_spawn[0][0] && mousePos.x<(comp_spawn[0][0]+comp_spawn[0][2]) ){
                    addComponent(_SRLATCH);
                    break;
                }
                else if (mousePos.x>comp_spawn[1][0] && mousePos.x<(comp_spawn[1][0]+comp_spawn[1][2]) ){
                    addComponent(_DFF);
                    break;
                }
                else if (mousePos.x>comp_spawn[2][0] && mousePos.x<(comp_spawn[2][0]+comp_spawn[2][2]) ){
                    addComponent(_TFF);
                    break;
                }
                else if (mousePos.x>comp_spawn[3][0] && mousePos.x<(comp_spawn[3][0]+comp_spawn[3][2]) ){
                    addComponent(_JKFF);
                    break;
                }
                else if (mousePos.x>comp_spawn[4][0] && mousePos.x<(comp_spawn[4][0]+comp_spawn[4][2]) ){
                    addComponent(_SRFF);
                    break;
                }
                else if (mousePos.x>comp_spawn[5][0] && mousePos.x<(comp_spawn[5][0]+comp_spawn[5][2]) ){
                    addComponent(_CLOCK);
                    break;
                }
            }
            if (mousePos.x>comp_spawn[7][0] && mousePos.x<(comp_spawn[7][2]+comp_spawn[7][0])){
                addComponent(_INPUT);
            }
            else if (mousePos.x>comp_spawn[8][0] && mousePos.x<(comp_spawn[8][2]+comp_spawn[8][0])){
                addComponent(_OUTPUT);
            }
        }

        //  spawn components change
        if (gate.mouseHover(mousePos)){
            gate.pressedFlag = true;
            comb.pressedFlag = false;
            ff.pressedFlag = false;
            type = _GATES;
        }
        else if (comb.mouseHover(mousePos)){
            comb.pressedFlag = true;
            gate.pressedFlag = false;
            ff.pressedFlag = false;
            type = _COMBINATIONAL;
        }
        else if (ff.mouseHover(mousePos)){
            ff.pressedFlag = true;
            comb.pressedFlag = false;
            gate.pressedFlag = false;
            type = _SEQUENTIAL;
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
        if (Component::selectedCompNo != -1){
            components[Component::selectedCompNo]->updateSelectedComp(mousePos, prevMousePos);
        }
        break;
    }

    case RELEASED:{
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
    else if (type == _CLOCK){
        std::cout<<"Added clock comp";
        if (availableIndex == -1){
            components[Component::componentNo] = new Clock(1000);
            components[Component::componentNo]->setValues(type, mousePos,-1);
        }
        else{
            delete components[availableIndex];
            components[availableIndex] = new Clock(1000);
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







