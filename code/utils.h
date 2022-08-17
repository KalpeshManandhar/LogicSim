#pragma once

#define ABS(X) ((X<0)?(-X):(X))
#define SELECT_GREEN 109, 226, 114, 255

struct vec2{        // 2d vector for coordinates 
    int x,y;
};

enum Pin_type{
    _IN, _OUT, _BLANKE
};

struct Pin{
    vec2 *pos;
    int *logic;
    Pin_type type;
};

enum c_type{
    _AND, _OR, _NOT, _NAND, _NOR, _XOR, _XNOR, _INPUT, _OUTPUT, _CLOCK, 
    _ADDER, _SUBTRACTOR, _4x2ENCODER, _2x4DECODER, _NOTHING
};

enum load_type{
    _GATES, _COMB, _FF
};