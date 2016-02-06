#include "upDownPlane.h"

void upDownPlane(int time, int drawTime) {
  emptyCube();

  byte currentIndex = 0;
  
  AlternatingLed** leds = new AlternatingLed*[PLANESIZE];
  
  for(byte x = CUBESIZE/4; x < 3*CUBESIZE/4; x++) {
    for(byte y = CUBESIZE/4; y < 3*CUBESIZE/4; y++) {
      xyz pos = {x, y, 0};
      xyz max = {x, y, CUBESIZE-1};
      leds[currentIndex++] = new AlternatingLed(pos, true, Direction::up, pos, max);
    }
  }
  
  for(byte x = 0; x < CUBESIZE; x++) {
    for (byte y = 0; y < CUBESIZE/4; y++) {
      xyz pos = {x, y, CUBESIZE-1};
      xyz min = {x, y, 0};
      leds[currentIndex++] = new AlternatingLed(pos, true, Direction::down, min, pos);
      
      xyz pos1 = {x, CUBESIZE-1-y, CUBESIZE-1};
      xyz min1 = {x, CUBESIZE-1-y, 0};
      leds[currentIndex++] = new AlternatingLed(pos1, true, Direction::down, min1, pos1);
    }
  }
  
  for(byte x = 0; x < CUBESIZE/4; x++) {
    for(byte y = CUBESIZE/4; y < 3*CUBESIZE/4; y++) {
      xyz pos = {x, y, CUBESIZE-1};
      xyz min = {x, y, 0};
      leds[currentIndex++] = new AlternatingLed(pos, true, Direction::down, min, pos);
      
      xyz pos1 = {CUBESIZE-1-x, y, CUBESIZE-1};
      xyz min1 = {CUBESIZE-1-x, y, 0};
      leds[currentIndex++] = new AlternatingLed(pos1, true, Direction::down, min1, pos1);
    }
  }

  NonBlockDelay timer;
  timer.delay(time);
  
  while(!timer.timeout()) {
    drawState(drawTime);
    
    for(byte i = 0; i < PLANESIZE; i++) {
      leds[i]->update();
    }
  }

  delete[] leds;
  leds = NULL;
}
