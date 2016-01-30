//=================================
// include guard
#ifndef __EFFECTS_H_INCLUDED__
#define __EFFECTS_H_INCLUDED__

#include "Delay.h"
#include "LinkedList.h"
#include "led.h"
#include "plane.h"
#include "pos.h"
#include "cube.h"


enum Anchor {BotFrontLeft, BotFrontRight, BotBackLeft, BotBackRight,
             TopFrontLeft, TopFrontRight, TopBackLeft, TopBackRight, Center, AnchorMax};
             
const Position anchorPositions[8] = {Position (0,0,0), Position (CUBESIZE-1,0,0), Position (0,CUBESIZE-1,0), Position (CUBESIZE-1,CUBESIZE-1,0), 
                                     Position (0,0,CUBESIZE-1), Position (CUBESIZE-1,0,CUBESIZE-1), Position (0,CUBESIZE-1,CUBESIZE-1), Position (CUBESIZE-1,CUBESIZE-1,CUBESIZE-1)};

/* EFFECTS */
void pieter(int, int = 200);
void waveSine(int, int = 200);

void movingPlane(int, int = 350);

void rectangleEdgesEffect(int = 400);
void rectangleEdges(byte, Anchor, bool);
void rectangleEdges(int, int, int, Position, bool);
void rectangleEdges(Position, Position, bool);

#endif
