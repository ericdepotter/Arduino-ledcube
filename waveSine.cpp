#include "waveSine.h"

void waveSine(int time, int drawTime) {
  emptyCube();
  
  byte currentIndex = 0;
  
  AlternatingLed** leds = new AlternatingLed*[PLANESIZE];
  
  for (byte xAndY = 0; xAndY < CUBESIZE; xAndY++) {
  	for (byte y = 0; y <= xAndY; y++) {
      byte x = xAndY - y;
  	  xyz pos = {x, y, xAndY};
      xyz min = {x, y, 0};
      xyz max = {x, y, CUBESIZE-1};

      leds[currentIndex++] = new AlternatingLed(pos, true, Direction::up, min, max);
  	}
  }

  for (byte xAndY = 0; xAndY < CUBESIZE - 1; xAndY++) {
  	for (byte y = 0; y <= xAndY; y++) {
      byte x = CUBESIZE - xAndY + y - 1;
  	  xyz pos = {x, CUBESIZE - y - 1, xAndY};
      xyz min = {x, CUBESIZE - y - 1, 0};
      xyz max = {x, CUBESIZE - y - 1, CUBESIZE-1};

      leds[currentIndex++] = new AlternatingLed(pos, true, Direction::down, min, max);
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