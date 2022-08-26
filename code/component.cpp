#include "component.h"
#include "SDL.h"
#include <iostream>


short Component::componentNo = 0;
short Component::selectedCompNo = -1;
Pin* Component::selectedPin = NULL;


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
    sendOp = true;
    computedFlag = false;
    for (i = 0; i<MAX_INPUTS; i++)
        inPin[i].pos = new vec2;
    for (i = 0; i<MAX_OUTPUTS; i++)
        outPin[i].pos = new vec2;
}

Component::~Component(){
    int i;
    for (i = 0; i<MAX_INPUTS; i++)
        delete inPin[i].pos;
    for (i = 0; i<MAX_OUTPUTS; i++)
        delete outPin[i].pos;
}

void Component::setValues(c_type type, vec2 &mousePos, int availableIndex){
    // sets the type of component
    this->type = type;

    setSprites();
    setPinNo();
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
    for (i = 0; i<outputNo; i++){
        outPin[i].pos->x  += compPos.x;
        outPin[i].pos->y  += compPos.y;
        outPin[i].type = _OUT;
        output[i] = -1;
        outPin[i].logic = &output[i];
    }
    std::cout<<"COmp added"<<index<<std::endl;
}

// sets the sprite source positions
void Component::setSprites(){
    if (type < 10){
        compPos.h = 72;
        spriteSrc.h = 72;
        spriteSrc.y = (type/5)*72;
    }
    else if (type == _8x1MUX || type == _1x8DEMUX){
        compPos.h = 216;
        spriteSrc.h = 216;
        spriteSrc.y = 648;
    }
    else if (type ==_CLOCK){
        compPos.h = 72;
        spriteSrc.h = 72;
        spriteSrc.y = 5*72;
    }
    else if (type < 20){
        compPos.h = 108;
        spriteSrc.y = 6*72;
        spriteSrc.h = 108;
    }
    else{
        compPos.h = 108;
        spriteSrc.y = 6*72 + 108;
        spriteSrc.h = 108;
    }

    spriteSrc.x = (type%5) * 146; 
}

// sets the number of input and output pins
void Component::setPinNo(){
    switch (type)
    {
    case _NOT:
        inputNo = 1;
        outputNo = 1;
        break;
    case _OUTPUT:
        outputNo = 0;
        inputNo = 1;
        break;
    case _CLOCK:
    case _INPUT:
        inputNo = 0;
        outputNo = 1;
        break;
    case _AND:
    case _OR:
    case _NAND:
    case _NOR:
    case _XOR:
    case _XNOR:
        inputNo = 2;
        outputNo = 1;
        break;
    case _ADDER:
    case _SUBTRACTOR:
        inputNo = 3;
        outputNo = 2;
        break;
    case _4x2ENCODER:
        inputNo = 5;
        outputNo = 2;
        break;
    case _2x4DECODER:
        inputNo = 3;
        outputNo = 4;
        break;
    case _8x1MUX:
        inputNo = 11;
        outputNo = 1;
        break;
    case _1x8DEMUX:
        inputNo = 4;
        outputNo = 8;
        break;
    case _DFF:
    case _TFF:
    case _SRLATCH:
        inputNo = 2;
        outputNo = 2;
        break;
    case _JKFF:
    case _SRFF:
        inputNo = 3;
        outputNo = 2;
        break;
    default:
        break;
    }

}

void Component::setPinPos(){
    // zero output pins
    if (type == _OUTPUT){               
        outPin[0].pos->x = -200;
        outPin[0].pos->y = -400;       
    }
    // two output pins
    else if (type == _ADDER || type == _SUBTRACTOR || type == _4x2ENCODER|| type == _DFF ||type == _SRLATCH ||type == _TFF ||type == _JKFF ||type == _SRFF){
        outPin[0].pos->x = 141;
        outPin[0].pos->y = 39;
        outPin[1].pos->x = 141;
        outPin[1].pos->y = 70;
    }
    // four output pins
    else if (type == _2x4DECODER){
        outPin[0].pos->x = 141;
        outPin[0].pos->y = 18;
        outPin[1].pos->x = 141;
        outPin[1].pos->y = 40;
        outPin[2].pos->x = 141;
        outPin[2].pos->y = 64;
        outPin[3].pos->x = 141;
        outPin[3].pos->y = 86;
    }
    else if (type == _8x1MUX){
        outPin[0].pos->x = 141;
        outPin[0].pos->y = 100;
    }
    else if (type == _1x8DEMUX){
        outPin[0].pos->x = 141;
        outPin[0].pos->y = 19;
        outPin[1].pos->x = 141;
        outPin[1].pos->y = 41;
        outPin[2].pos->x = 141;
        outPin[2].pos->y = 65;
        outPin[3].pos->x = 141;
        outPin[3].pos->y = 87;
        outPin[4].pos->x = 141;
        outPin[4].pos->y = 109;
        outPin[5].pos->x = 141;
        outPin[5].pos->y = 131;
        outPin[6].pos->x = 141;
        outPin[6].pos->y = 155;
        outPin[7].pos->x = 141;
        outPin[7].pos->y = 177;
    }
    // one output pin
    else{
        outPin[0].pos->x = 141;
        outPin[0].pos->y = 35;
    }
    
    // only one input pin
    if (type == _NOT || type == _OUTPUT){           
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 36;
    }
    // zero input pins
    else if (type == _INPUT || type == _CLOCK){                       
        inPin[0].pos->x = -200;
        inPin[0].pos->y = -400;
    }
    // three input pins
    else if (type == _ADDER || type == _SUBTRACTOR){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 30;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 52;
        inPin[2].pos->x = 4;
        inPin[2].pos->y = 80;
    }
    // four input pins
    else if (type ==  _4x2ENCODER){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 18;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 40;
        inPin[2].pos->x = 4;
        inPin[2].pos->y = 64;
        inPin[3].pos->x = 4;
        inPin[3].pos->y = 86;
    }
    // two input pins but larger
    else if (type == _2x4DECODER){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 38;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 70;
        inPin[2].pos->x = 73;
        inPin[2].pos->y = 105;
    }
    else if (type == _SRLATCH){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 38;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 70;
    }
    else if (type == _DFF || type == _TFF){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 30;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 52;
    }
    else if (type == _SRFF || type == _JKFF){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 30;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 52;
        inPin[2].pos->x = 4;
        inPin[2].pos->y = 79;
    }
    else if (type == _8x1MUX){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 19;
        inPin[1].pos->x = 4;
        inPin[1].pos->y = 41;
        inPin[2].pos->x = 4;
        inPin[2].pos->y = 65;
        inPin[3].pos->x = 4;
        inPin[3].pos->y = 87;
        inPin[4].pos->x = 4;
        inPin[4].pos->y = 109;
        inPin[5].pos->x = 4;
        inPin[5].pos->y = 131;
        inPin[6].pos->x = 4;
        inPin[6].pos->y = 155;
        inPin[7].pos->x = 4;
        inPin[7].pos->y = 177;
        inPin[8].pos->x = 51;
        inPin[8].pos->y = 209;
        inPin[9].pos->x = 72;
        inPin[9].pos->y = 209;
        inPin[10].pos->x = 97;
        inPin[10].pos->y = 209;
    }
    else if (type == _1x8DEMUX){
        inPin[0].pos->x = 4;
        inPin[0].pos->y = 100;
        inPin[1].pos->x = 51;
        inPin[1].pos->y = 209;
        inPin[2].pos->x = 72;
        inPin[2].pos->y = 209;
        inPin[3].pos->x = 97;
        inPin[3].pos->y = 209;
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
        for (i = 0; i<outputNo; i++){
            if ((mousePos.x > outPin[i].pos->x - 10) && (mousePos.x < outPin[i].pos->x +10) && (mousePos.y > outPin[i].pos->y - 10) && (mousePos.y < outPin[i].pos->y +10)){
                pinHover = 1;
                selectedPin = &outPin[i];
                return(true);
            }
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
    // updates the position of the component
    compPos.x += (mousePos.x - prev.x);
    compPos.y += (mousePos.y - prev.y);

    // updates position of the pins
    int i;
    for (i = 0; i<inputNo; i++){
        inPin[i].pos->x  += (mousePos.x - prev.x);
        inPin[i].pos->y  += (mousePos.y - prev.y);
    }
    for (i = 0; i<outputNo; i++){
        outPin[i].pos->x  += (mousePos.x - prev.x);
        outPin[i].pos->y  += (mousePos.y - prev.y);
    }
}

void Component::removeComponent(){
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

int Component::getOutputNo(){
    return(outputNo);
}

Pin * Component::getInPinAddress(int i){
    return(&inPin[i]);
}

Pin* Component::getOutPinAddress(int i){
    return(&outPin[i]);
}

int * Component::getInputs(){
    return(input);
}

int * Component::getOutputs(){
    return(output);
}

bool Component::sendOutput(){
    return(sendOp);
}

void Component::setSendOp(bool send){
    sendOp = send;
}

void Component::setOutput(int op){
    int i;
    if (op == -1) op = 3;

    // assigns the bits of the bitmask to the outputs eg 1000
    // output[3] = 0
    // output[2] = 0
    // output[1] = 0
    // output[0] = 1
    // 0123 pins go from top to bottom
    for (i=0; i< outputNo; i++){
        output[outputNo - 1 -i] = (op>>i)&1;
    }
}

SDL_Rect Component::getCompRect(){
    return(compPos);
}

void Component::setComputedFlag(bool flag){
    computedFlag = flag;
}


//  INPUT COMPONENT FUNCTIONS

// position of the input button
void InputComponent::setButtonPos(){
    inputButton.button.x = 80;
    inputButton.button.y = 15;
    inputButton.button.w = 40;
    inputButton.button.h = 40;
}

// what happens when the button is pressed?
void InputComponent::onPressed(){
    output[0] = (output[0] == 1)?0:1;
}

void InputComponent::updateSelectedComp(vec2 &mousePos, vec2 &prev){
    Component::updateSelectedComp(mousePos, prev);
    // updates the button position
    inputButton.button.x += (mousePos.x - prev.x);
    inputButton.button.y += (mousePos.y - prev.y);
}

void InputComponent::setValues(c_type type, vec2 &mousePos, int availableIndex){
    Component::setValues(type, mousePos, availableIndex);
    setButtonPos();
    inputButton.button.x += compPos.x;
    inputButton.button.y += compPos.y;
    output[0] = 0;
}

void InputComponent::draw(SDL_Renderer* renderer, SDL_Texture* spritesheet){
    SDL_RenderCopy(renderer, spritesheet, &spriteSrc, &compPos);
    
    SDL_Rect srcText = {0,701, 20,20}, destText = {0, 0, 20, 30};
    destText.x = inputButton.button.x + 10;
    destText.y = inputButton.button.y + 5;
    //  1 = RED button
    if (output[0] == 1){
        srcText.x = 334;
        SDL_SetRenderDrawColor(renderer, 200, 0, 0,255);
    }
    //  0 = BLUE button
    else {
        srcText.x = 354;
        SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    }
    SDL_RenderFillRect(renderer, &inputButton.button);
    SDL_RenderCopy(renderer, spritesheet, &srcText, &destText);
}


bool InputComponent::mouseHover(vec2 &mousePos, int & pinHover){
    // if button is pressed, isPressed() is called
    if (inputButton.mouseHover(mousePos))
        onPressed();
    return(Component::mouseHover(mousePos, pinHover));
}


// OUTPUT COMPONENT FUNCTIONS
// sets the initial position of the display box
void OutputComponent::setDisplayPos(){
    display.x = 15;
    display.y = 18;
    display.w = 30;
    display.h = 30;
}

void OutputComponent::setValues(c_type type, vec2 &mousePos, int availableIndex){
    Component::setValues(type, mousePos, availableIndex);
    setDisplayPos();
    display.x += compPos.x;
    display.y += compPos.y;
}

void OutputComponent::updateSelectedComp(vec2 &mousePos, vec2 &prev){
    Component::updateSelectedComp(mousePos, prev);
    // updates the display position
    display.x += (mousePos.x - prev.x);
    display.y += (mousePos.y - prev.y);
}

void OutputComponent::draw(SDL_Renderer* renderer, SDL_Texture* spritesheet){
    SDL_RenderCopy(renderer, spritesheet, &spriteSrc, &compPos);
    
    //  1 = RED 
    if (input[0] == 1)
        SDL_SetRenderDrawColor(renderer, 200, 0, 0,255);
    //  0 = BLUE
    else 
        SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    SDL_RenderFillRect(renderer, &display);
}

// default frequency of clock 1HZ
Clock::Clock(float timePeriod){
    T = timePeriod;
    duration = 0;
    sendOp = true;
}

void Clock::setOutput(int FPS){//60
    float Tseconds = T/1000; //1
    // sendOp sends HIGH only on first frame for transition activation
    sendOp = false;
    sendFlipFlopOutput(false);
    // half cycle 
    if (duration == ((FPS * Tseconds/2 ))){
        sendOp = true;
        sendFlipFlopOutput(true);
        output[0] = 1;
    }
    // full cycle
    else if (duration == FPS * Tseconds){
        output[0] = 0;
        duration = 0;
    }
    duration ++;
}

void Clock::sendFlipFlopOutput(bool send){
    int i;
    for (i = 0;i<Component::componentNo;i++){
        switch (components[i]->getType()){
            case _JKFF:
            case _SRLATCH:
            case _SRFF:
            case _TFF:
            case _DFF:
                components[i]->setSendOp(send);
        }
    }
    int memory;
}