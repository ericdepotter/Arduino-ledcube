//=================================
// include guard
#ifndef __RECTANGLES_H_INCLUDED__
#define __RECTANGLES_H_INCLUDED__

#include "cube.h"
#include "Delay.h"
#include "pos.h"

enum Anchor {BotFrontLeft, BotFrontRight, BotBackLeft, BotBackRight,
             TopFrontLeft, TopFrontRight, TopBackLeft, TopBackRight, Center, AnchorMax};
             
const Position anchorPositions[8] = {Position (0,0,0), Position (CUBESIZE-1,0,0), Position (0,CUBESIZE-1,0), Position (CUBESIZE-1,CUBESIZE-1,0), 
                                     Position (0,0,CUBESIZE-1), Position (CUBESIZE-1,0,CUBESIZE-1), Position (0,CUBESIZE-1,CUBESIZE-1), Position (CUBESIZE-1,CUBESIZE-1,CUBESIZE-1)};

/* EFFECTS */
void rectangleEdgesEffect(int = 400);
void rectangleEdges(byte, Anchor, bool);
void rectangleEdges(int, int, int, Position, bool);
void rectangleEdges(Position, Position, bool);

#endif
