#pragma once

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
    _AND, _OR, _NOT, _NAND, _NOR, _XOR, _XNOR, _INPUT, _OUTPUT, _NOTHING, _ADDER, _SUBTRACTOR, _4x2ENCODER, _2x4DECODER
};