#include "cube.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

byte drawRow = 0;


byte ledPin[16] = {4, 5, 8, 9, 7, 6, A0, A1, 10, 11, 0, 1, 13, 12, 3, 2};
byte ledPinCount = PLANESIZE;
byte planePin[4] = {A2, A3, A4, A5};
byte planePinCount  = CUBESIZE;


byte pinIndex(byte x, byte y) {
  return x + CUBESIZE*y;
}


byte getLedPin(byte x, byte y) {
  return ledPin[pinIndex(x, y)];
}


bool cachedState[4][16] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

bool currentState[4][16] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
bool previousState[4][16] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void drawState(int milli) {
  // Disable interrupts: we do not want to draw half the correct state ;).
  noInterrupts();
  
  for (byte z = 0; z < CUBESIZE; z++) {
    for (byte xy = 0; xy < PLANESIZE; xy++) {
      cachedState[z][xy] = currentState[z][xy];
    }
  }
  // Eisable interrupts: we want to be able to draw again.
  interrupts();
  
  delay(milli);
}


void setupState() {
  emptyCube();
  drawState();
}

bool getLedState(byte x, byte y, byte z) {
  if (inRange(x,y,z)) {
    return currentState[z][pinIndex(x,y)];
  }
}

// Draw

void planesOff(){
  for(byte thisPlane = 0; thisPlane < CUBESIZE; thisPlane++){
    digitalWrite(planePin[thisPlane], HIGH);
  }
}

void allLedsOff(){
  for(byte thisPin = 0; thisPin < PLANESIZE; thisPin++){
    digitalWrite(ledPin[thisPin], LOW);
  }
}

void drawCube() {
  // Disable interrupts: we do not want to draw half the correct state ;).
  noInterrupts();
  
  digitalWrite(planePin[drawRow], HIGH); //turn off previous plane
  byte plane = (drawRow + 1) % CUBESIZE;
  allLedsOff();
  
  digitalWrite(planePin[plane], LOW); // turn on this plane
  
  for(byte x = 0; x < CUBESIZE; x++){
    for(byte y = 0; y < CUBESIZE; y++) {
      digitalWrite(getLedPin(x,y), cachedState[plane][pinIndex(x,y)]); // set it to whatever the state says it should be
    }
  }
    
  drawRow = plane;
  interrupts();
}


// Basic functions

void ledOn(byte x, byte y, byte z) {
  if (inRange(x,y,z)) {
    currentState[z][pinIndex(x, y)] = true;
  }
}

void ledOff(byte x, byte y, byte z) {
  if (inRange(x,y,z)) {
    currentState[z][pinIndex(x, y)] = false;
  }
}

void ledFlip(byte x, byte y, byte z) {
  if (inRange(x,y,z)) {
    currentState[z][pinIndex(x, y)] = !currentState[z][pinIndex(x, y)];
  }
}

void led(byte x, byte y, byte z, bool state) {
  if (inRange(x,y,z)) {
    currentState[z][pinIndex(x, y)] = state;
  }
}

//Lines

void lineX(byte x1, byte x2, byte y, byte z, bool state) {
  if (x2 < x1) {
    swap(&x1, &x2);
  }
  x1 = max(0, x1);
  x2 = min(x2, CUBESIZE-1);
 
  for (byte x = x1; x <= x2; x++) {
     currentState[z][pinIndex(x, y)] = state;
  }  
}

void lineY(byte y1, byte y2, byte x, byte z, bool state) {
  if (y2 < y1) {
    swap(&y1, &y2);
  }
  y1 = max(0, y1);
  y2 = min(y2, CUBESIZE-1);
 
  for (byte y = y1; y <= y2; y++) {
     currentState[z][pinIndex(x, y)] = state;
  }  
}

void lineZ(byte z1, byte z2, byte x, byte y, bool state) {
  if (z2 < z1) {
    swap(&z1, &z2);
  }
  z1 = max(0, z1);
  z2 = min(z2, CUBESIZE-1);
 
  for (byte z = z1; z <= z2; z++) {
     currentState[z][pinIndex(x, y)] = state;
  }  
}

// Planes
void planeX(byte x, bool state) {
  for (byte y = 0; y < CUBESIZE; y++) {
    for (byte z = 0; z < CUBESIZE; z++) {
      currentState[z][pinIndex(x, y)] = state;
    }
  }
}

void planeY(byte y, bool state) {
  for (byte x = 0; x < CUBESIZE; x++) {
    for (byte z = 0; z < CUBESIZE; z++) {
      currentState[z][pinIndex(x, y)] = state;
    }
  }
}

void planeZ(byte z, bool state) {
  for (byte xy = 0; xy < PLANESIZE; xy++) {
    currentState[z][xy] = state;
  }
}


void diagonalPlaneXY00(bool state) {
  for (byte xy = 0; xy < CUBESIZE; xy++) {
    byte pin = pinIndex(xy, xy);
    
    for (byte z = 0; z < CUBESIZE; z++) {
      currentState[z][pin] = state;
    }
  }
}

void diagonalPlaneXY03(bool state) {
  for (byte xy = 0; xy < CUBESIZE; xy++) {
    byte pin = pinIndex(CUBESIZE-1 - xy, xy);
    
    for (byte z = 0; z < CUBESIZE; z++) {
      currentState[z][pin] = state;
    }
  }
}

void diagonalPlaneXZ00(bool state) {
  for (byte xz = 0; xz < CUBESIZE; xz++) {    
    for (byte y = 0; y < CUBESIZE; y++) {
      currentState[xz][pinIndex(xz, y)] = state;
    }
  }
}

void diagonalPlaneXZ03(bool state) {
  for (byte xz = 0; xz < CUBESIZE; xz++) {    
    for (byte y = 0; y < CUBESIZE; y++) {
      currentState[CUBESIZE-1 - xz][pinIndex(xz, y)] = state;
    }
  }
}

void diagonalPlaneYZ00(bool state){
  for (byte yz = 0; yz < CUBESIZE; yz++) {    
    for (byte x = 0; x < CUBESIZE; x++) {
      currentState[yz][pinIndex(x, yz)] = state;
    }
  }
}

void diagonalPlaneYZ03(bool state) {
  for (byte yz = 0; yz < CUBESIZE; yz++) {    
    for (byte x = 0; x < CUBESIZE; x++) {
      currentState[CUBESIZE-1 - yz][pinIndex(x, yz)] = state;
    }
  }
}


// Cube //

void setCube(bool state) {
  for (byte z = 0; z < CUBESIZE; z++) {
    planeZ(z, state);
  }
}

void fillCube() {
  setCube(true);
}

void emptyCube() {
  setCube(false);
}

// Helper methods

bool inRange(byte x, byte y, byte z) {
  return (x >= 0 && x < CUBESIZE && 
          y >= 0 && y < CUBESIZE &&
          z >= 0 && z < CUBESIZE);
}

template<class T> void swap(T* x,T* y) {
    T t;
    t = *x;
    *x = *y;
    *y = t;
}


