//=================================
// include guard
#ifndef __CUBE_H_INCLUDED__
#define __CUBE_H_INCLUDED__

#include <stdint.h>;
 
#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define byte uint8_t

// The pins are left -> right, bot -> top
extern byte ledPin[16];
extern byte ledPinCount;
extern byte planePin[4];
extern byte planePinCount;


byte getLedPin(byte, byte);

void drawState(int = 0);

void setupState();
bool getLedState(byte, byte, byte);

// DRAW
void planesOff();
void allLedsOff();
void drawCube();

// Light leds
void ledOn(byte, byte, byte);
void ledOff(byte, byte, byte);
void ledFlip(byte, byte, byte);
void led(byte, byte, byte, bool);

void lineX(byte, byte, byte, byte, bool);
void lineY(byte, byte, byte, byte, bool);
void lineZ(byte, byte, byte, byte, bool);

void planeX(byte, bool);
void planeY(byte, bool);
void planeZ(byte, bool);

void diagonalPlaneXY00(bool);
void diagonalPlaneXY03(bool);
void diagonalPlaneXZ00(bool);
void diagonalPlaneXZ03(bool);
void diagonalPlaneYZ00(bool);
void diagonalPlaneYZ03(bool);

void fillCube();
void emptyCube();

bool inRange(byte, byte, byte);
template<class T> void swap(T*,T*);

#endif // __CUBE_H_INCLUDED__
