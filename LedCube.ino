#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <TimerOne.h>

#include "cube.h"
#include "led.h"
#include "plane.h"
#include "effects.h"
#include "Delay.h"

//boolean currentState[4][16] = {
//{0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//{0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
//{0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
//{0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0}
//}; // demo - initialized with this pattern

#define LEDFPS 50
#define CUBEFPS 10

/*** HACK ***/
void softwareReset() {// Restarts program from beginning but does not reset the peripherals and registers
  asm volatile ("  jmp 0");  
}

int times = 0;

void setup()
{
  // set up LED pins as output (active HIGH)
  for (byte pin = 0; pin < PLANESIZE; pin++) {
    pinMode(ledPin[pin], OUTPUT);
    digitalWrite(ledPin[pin], LOW);
  }
  // set up plane pins as outputs (active LOW)
  for (byte pin = 0; pin < CUBESIZE; pin++) {
    pinMode(planePin[pin], OUTPUT);
    digitalWrite(planePin[pin], HIGH);
  }
  
//  Serial.begin(9600);
//  Serial.println("");
  
  // Test Persistence of Vision
//  testPOV();

  Timer1.initialize(1000000/LEDFPS/CUBESIZE);
  Timer1.attachInterrupt(drawCube); // drawCube to run every 1000000/LEDFPS/CUBESIZE microseconds

  diagnostics();
}


void loop() { 
  if (++times == 5) {
    times = 0;
    softwareReset();
  }
  
  emptyCube();
  delay(1000);  
  //effects
  for(byte i = 0; i < 2; i++) {
    rectangleEdgesEffect();
  }
  
  emptyCube(); 
  delay(1000);
  waveSine(30000);
  
  emptyCube();
  delay(1000); 
  movingPlane(30000);
   
  emptyCube();
  delay(1000); 
  pieter(30250);
  
  emptyCube();
//  for (int z = 0; z < CUBESIZE; z++) {
//    planeZ(z, true);
//    drawState(500);
//    planeZ(z, false);
//  }
//  for (int x = 0; x < CUBESIZE; x++) {
//    planeX(x, true);
//    drawState(500);
//    planeX(x, false);
//  }
//  for (int y = 0; y < CUBESIZE; y++) {
//    planeY(y, true);
//    drawState(500);
//    planeY(y, false);
//  }
}

void diagnostics() {
  for (byte z = 0; z < CUBESIZE; z++) {
    for (byte y = 0; y < CUBESIZE; y++) {
      for (byte x = 0; x < CUBESIZE; x++) {
        ledOn(x,y,z);
        drawState(200);
        ledOff(x,y,z);
      }
    }
  }
  
  for (byte z = 0; z < CUBESIZE; z++) {
    planeZ(z, true);
    drawState(750);
  }
}
//
void simple_diagnostics() {
  planesOff();
  allLedsOff();
  
  for (byte z = 0; z < CUBESIZE; z++) {
    digitalWrite(planePin[z], LOW); // turn on this plane
    
    for (byte y = 0; y < CUBESIZE; y++) {
      for (byte x = 0; x < CUBESIZE; x++) {
        digitalWrite(getLedPin(x,y), HIGH); // turn the led on
        delay(200);
        digitalWrite(getLedPin(x,y), LOW); // turn the led off
      }
    }  
    
    digitalWrite(planePin[z], HIGH); //turn off this plane before moving to the next one 
  }
}


void testPOV() {
  rectangleEdges(CUBESIZE, Center, true);
  drawState();
  
  NonBlockDelay d;
  int time = 5000;
  
  for (byte FPS = 2; FPS <= 10; FPS += 2) {
    d.delay(time);
    
    while (!d.timeout()) {
      drawCube();
      delay(1000/FPS/CUBESIZE);
    }
  }
 
  for (byte FPS = 15; FPS <= 20; FPS += 5) {
    d.delay(time);
    
    while (!d.timeout()) {
      drawCube();
      delay(1000/FPS/CUBESIZE);
    }
  }
 
  for (byte FPS = 30; FPS <= 50; FPS += 10) {
    d.delay(time);
    
    while (!d.timeout()) {
      drawCube();
      delay(1000/FPS/CUBESIZE);
    }
  }
  
  planesOff();
}




