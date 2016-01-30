#include "effects.h";

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Delay.h"
#include "LinkedList.h"
#include "led.h"; 
#include "plane.h"; 

void pieter(int time, int drawTime) {
  emptyCube();
  
  LinkedList<AlternatingLed*> leds = LinkedList<AlternatingLed*>();
  
  for(byte x = 1; x < CUBESIZE-1;x++) {
    for(byte y = 1; y < CUBESIZE-1; y++) {
      xyz pos = {x, y, 0};
      xyz max = {x, y, CUBESIZE-1};
      leds.add(new AlternatingLed(pos, true, Direction::up, pos, max));
    }
  }
  
  for(byte x = 0; x < CUBESIZE; x++) {
    xyz pos = {x, 0, CUBESIZE-1};
    xyz min = {x, 0, 0};
    leds.add(new AlternatingLed(pos, true, Direction::down, min, pos));
    
    xyz pos1 = {x, CUBESIZE-1, CUBESIZE-1};
    xyz min1 = {x, CUBESIZE-1, 0};
    leds.add(new AlternatingLed(pos1, true, Direction::down, min1, pos1));
  }
  
  for(byte y = 1; y < CUBESIZE-1; y++) {
    xyz pos = {0, y, CUBESIZE-1};
    xyz min = {0, y, 0};
    leds.add(new AlternatingLed(pos, true, Direction::down, min, pos));
    
    xyz pos1 = {CUBESIZE-1, y, CUBESIZE-1};
    xyz min1 = {CUBESIZE-1, y, 0};
    leds.add(new AlternatingLed(pos1, true, Direction::down, min1, pos1));
  }

  NonBlockDelay timer;
  timer.delay(time);
  
  while(!timer.timeout()) {
    drawState(drawTime);
    
    for(byte i = 0; i < leds.size(); i++) {
      leds.get(i)->update();
    }
  }
}

void waveSine(int time, int drawTime) {
  emptyCube();
  
  LinkedList<AlternatingLed*> leds = LinkedList<AlternatingLed*>();
  
  for(byte x = 0; x < CUBESIZE-1; x++) {
    xyz pos = {x, 0, x};
    xyz min = {x, 0, 0};
    xyz max = {x, 0, CUBESIZE-1};
    leds.add(new AlternatingLed(pos, true, Direction::up, min, max));
    
    xyz pos1 = {x, CUBESIZE-1, CUBESIZE-1 - x};
    xyz min1 = {x, CUBESIZE-1, 0};
    xyz max1 = {x, CUBESIZE-1, CUBESIZE-1};
    leds.add(new AlternatingLed(pos1, true, Direction::down, min1, max1));
  }
  
  xyz pos = {CUBESIZE-1, 0, CUBESIZE-1};
  xyz min = {CUBESIZE-1, 0, 0};
  leds.add(new AlternatingLed(pos, true, Direction::down, min, pos));
  
  xyz pos1 = {CUBESIZE-1, CUBESIZE-1, 0};
  xyz max1 = {CUBESIZE-1, CUBESIZE-1, CUBESIZE-1};
  leds.add(new AlternatingLed(pos1, true, Direction::up, pos1, max1));
  
  for(byte y = 1; y < CUBESIZE-1; y++) {
    xyz pos = {0, y, y};
    xyz min = {0, y, 0};
    xyz max = {0, y, CUBESIZE-1};
    leds.add(new AlternatingLed(pos, true, Direction::down, min, max));
    
    xyz pos1 = {CUBESIZE-1, y, CUBESIZE-1 - y};
    xyz min1 = {CUBESIZE-1, y, 0};
    xyz max1 = {CUBESIZE-1, y, CUBESIZE-1};
    leds.add(new AlternatingLed(pos1, true, Direction::up, min1, max1));
  }

  NonBlockDelay timer;
  timer.delay(time);
  
  while(!timer.timeout()) {
    drawState(drawTime);
    
    for(byte i = 0; i < leds.size(); i++) {
      leds.get(i)->update();
    }
  }
  
  for(byte i = 0; i < leds.size(); i++) {
      delete leds.get(i);
  }
}


void movingPlane(int time, int drawTime) {
  Plane* plane = new NormalPlane(X, 0);
//  Plane* inverse = new InverseTransformPlane(X, CUBESIZE-1);
  
  drawState(drawTime);
  
  NonBlockDelay timer;
  timer.delay(time);
  
  while(!timer.timeout()) {
    LinkedList<String> possible = plane->getLegalRotations();
    
    possible.add("sendPlaneDiffuse");
    
    String chosen = possible.get(random(possible.size()));
    
    if (chosen == "sendPlaneDiffuse") {
      plane->sendPlaneDiffuse((byte)drawTime/2.5);
    } else if (chosen == "rotateUp") {
      plane->rotateUp(drawTime);
//      inverse->rotateUp(drawTime);
    } else if (chosen == "rotateDown") {
      plane->rotateDown(drawTime);
//      inverse->rotateDown(drawTime);
    } else if (chosen == "rotateLeft") {
      plane->rotateLeft(drawTime);
//      inverse->rotateLeft(drawTime);
    } else if (chosen == "rotateRight") {
      plane->rotateRight(drawTime);
//      inverse->rotateRight(drawTime);
    } else if (chosen == "rotateFront") {
      plane->rotateFront(drawTime);
//      inverse->rotateFront(drawTime);
    } else {
      plane->rotateBack(drawTime);
//      inverse->rotateBack(drawTime);
    }
  }
}


/*******************
 * Rectangle Edges *
 *******************/
 
void rectangleEdgesEffect(int drawTime) {  
  emptyCube();
  drawState();
  
  Anchor anchor;
  for(byte i1 = AnchorMax; i1 >= 1; i1--) {
    byte i = i1 - 1;
    anchor = Anchor(i);
    
    for (byte size = CUBESIZE; size >= 1; size--) {
      rectangleEdges(size, anchor, true);
      drawState(drawTime);
      rectangleEdges(size, anchor, false);
    }
    
    for (byte size = 1; size <= CUBESIZE; size++) {
      rectangleEdges(size, anchor, true);
      drawState(drawTime);
      rectangleEdges(size, anchor, false);
    }
  }
  
  rectangleEdges(CUBESIZE, Center, true);
}


void rectangleEdges(byte size, Anchor anchor, bool state) {
  if (size == 0)
    return;
  
  switch (anchor) {
    case Center: {
      if (size >= (CUBESIZE/2))
        size = (CUBESIZE/2);
      
      byte left = (CUBESIZE/2) - size;
      byte right = (CUBESIZE/2) + size - 1; 
      
      rectangleEdges(Position (left,left,left), Position (right,right,right), state);
      break;
    }
    default: {
      rectangleEdges(size, size, size, anchorPositions[anchor], state);
      break;
    }
  }
}

void rectangleEdges(int xsize, int ysize, int zsize, Position anchor, bool state) {
  xsize -= 1; ysize -= 1; zsize -= 1;
  
  if (anchor.getX() > CUBESIZE/2)
    xsize = -xsize;
  
  if (anchor.getY() > CUBESIZE/2)
    ysize = -ysize;
  
  if (anchor.getZ() > CUBESIZE/2)
    zsize = -zsize;
  
  
  rectangleEdges(anchor, anchor.addPos(Position (xsize, ysize, zsize)), state);
}

void rectangleEdges(Position pos1, Position pos2, bool state) {
  xyz xyz1 = pos1.getPos();
  xyz xyz2 = pos2.getPos();
  
  // horizontal lines
  lineX(xyz1.x, xyz2.x, xyz1.y, xyz1.z, state);
  lineX(xyz1.x, xyz2.x, xyz2.y, xyz1.z, state);
  lineX(xyz1.x, xyz2.x, xyz1.y, xyz2.z, state);
  lineX(xyz1.x, xyz2.x, xyz2.y, xyz2.z, state);
  
  lineY(xyz1.y, xyz2.y, xyz1.x, xyz1.z, state);
  lineY(xyz1.y, xyz2.y, xyz2.x, xyz1.z, state);
  lineY(xyz1.y, xyz2.y, xyz1.x, xyz2.z, state);
  lineY(xyz1.y, xyz2.y, xyz2.x, xyz2.z, state);
  
  // vertical lines
  lineZ(xyz1.z, xyz2.z, xyz1.x, xyz1.y, state);
  lineZ(xyz1.z, xyz2.z, xyz2.x, xyz1.y, state);
  lineZ(xyz1.z, xyz2.z, xyz1.x, xyz2.y, state);
  lineZ(xyz1.z, xyz2.z, xyz2.x, xyz2.y, state);
}
