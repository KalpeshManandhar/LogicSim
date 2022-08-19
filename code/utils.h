#pragma once

#define ABS(X) ((X<0)?(-X):(X))
#define SELECT_GREEN 109, 226, 114, 255
#define BACKGROUND_BLUE 68,75,110, 255 
#define REMOVE_AREA_BLUE 59, 66, 86, 255
#define SPAWN_AREA_BLACK 45, 57, 72, 255
// #define SPAWN_AREA_BLACK 57, 57, 62, 255

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
    _AND, _OR, _NOT, _NAND, _NOR, _XOR, _XNOR, _INPUT, _OUTPUT, _blank,
    _ADDER, _SUBTRACTOR, _4x2ENCODER, _2x4DECODER, _8x1MUX, _1x8DEMUX, _INPUT2, _OUTPUT2, _blank2, _blank3,
    _SRLATCH, _DFF, _TFF, _JKFF, _SRFF, _CLOCK, _INPUT3, _OUTPUT3, 
    _NOTHING
};

enum load_type{
    _GATES, _COMBINATIONAL, _SEQUENTIAL
};