#include "plane.h"

/**********
** Plane **
***********/
NormalPlane::NormalPlane(Axis axis, byte level) {
  offset = level;
  
  switch (axis) {
    case X:
      planeX(offset, true);
  
      if (offset < CUBESIZE/2)
        transformer = new PlaneLeftTransformer(this);
      else
        transformer = new PlaneRightTransformer(this);
      break;
    
    case Y:
      planeY(offset, true);
  
      if (offset < CUBESIZE/2)
        transformer = new PlaneFrontTransformer(this);
      else
        transformer = new PlaneBackTransformer(this);
      break;
      
    case Z:
      planeZ(offset, true);
  
      if (offset < CUBESIZE/2)
        transformer = new PlaneBotTransformer(this);
      else
        transformer = new PlaneTopTransformer(this);
      break;
  }
  
  drawState();
}

void NormalPlane::rotateUp(int delayTime) {
  transformer->rotateUp(delayTime);
}

void NormalPlane::rotateDown(int delayTime) {
  transformer->rotateDown(delayTime);
}

void NormalPlane::rotateLeft(int delayTime) {
  transformer->rotateLeft(delayTime);
}

void NormalPlane::rotateRight(int delayTime) {
  transformer->rotateRight(delayTime);
}

void NormalPlane::rotateFront(int delayTime) {
  transformer->rotateFront(delayTime);
}

void NormalPlane::rotateBack(int delayTime) {
  transformer->rotateBack(delayTime);
}

//
//InverseTransformPlane::InverseTransformPlane(Axis axis, int offset) {
//  plane = new NormalPlane(axis, offset);
//}
//
//InverseTransformPlane::InverseTransformPlane(Plane* plane) {
//  this->plane = plane;
//}
//
//void InverseTransformPlane::rotateUp(int delayTime) {
//  plane->rotateDown(delayTime);
//}
//
//void InverseTransformPlane::rotateDown(int delayTime) {
//  plane->rotateUp(delayTime);
//}
//
//void InverseTransformPlane::rotateLeft(int delayTime) {
//  plane->rotateRight(delayTime);
//}
//
//void InverseTransformPlane::rotateRight(int delayTime) {
//  plane->rotateLeft(delayTime);
//}
//
//void InverseTransformPlane::rotateFront(int delayTime) {
//  plane->rotateBack(delayTime);
//}
//
//void InverseTransformPlane::rotateBack(int delayTime) {
//  plane->rotateFront(delayTime);
//}


/*********************
** PlaneTransformer **
*********************/
PlaneTransformer::PlaneTransformer(Plane* planeRef) {
  plane = planeRef;
}

void PlaneTransformer::rotate(planeCallback plane1, diagonalCallback diagonal, planeCallback plane2, PlaneTransformer* newTrans, byte newOffset, int drawTime) {
  plane1(plane->offset, false);
  diagonal(true);
  drawState(drawTime);
  
  plane->offset = newOffset;
  diagonal(false);
  plane2(plane->offset, true);
  
  plane->setTransformer(newTrans);
  drawState(drawTime);
}

void PlaneTransformer::sendPlane(int drawTime) {
  LinkedList<Led>* planeLeds = this->getLeds();
  xyz direction = this->getDirection();
  
  while(planeLeds->size() > 0) {
    int index = random(planeLeds->size());
    Led led = planeLeds->remove(index);
    
    for (int i = 1; i < CUBESIZE; i++) {
      led.move(direction);
    }
    
    drawState(drawTime);
//    delete &led;
  }
  
  delete planeLeds;
  plane->setTransformer(this->getOppositePlaneTransformer());
  plane->offset = CUBESIZE-1 - plane->offset;
  drawState(drawTime);
}

void PlaneTransformer::sendPlaneDiffuse(int drawTime) {
  LinkedList<Led>* planeLeds = this->getLeds();
  LinkedList<Led>* moving = new LinkedList<Led>();
  xyz direction = this->getDirection();
  
  while(planeLeds->size() > 0 || moving->size() > 0) {
    if (planeLeds->size() > 0) {
      int index = random(planeLeds->size());
      Led led = planeLeds->remove(index);
      
      moving->add(led);
    }
    
    for (int i = 0; i < moving->size(); ) {
      Led led = moving->get(i);
      
      if (led.canMove(direction)) {
        led.move(direction);
        moving->set(i, led);
        i++;
      } else {
        moving->remove(i);
      }
    }
    
    drawState(drawTime);
  }
  
  delete planeLeds;
  delete moving;
  plane->setTransformer(this->getOppositePlaneTransformer());
  plane->offset = CUBESIZE-1 - plane->offset;
  drawState(drawTime);
}

// Plane Top //

PlaneTopTransformer::PlaneTopTransformer(Plane* planeRef) : PlaneTransformer(planeRef) {}

LinkedList<String> PlaneTopTransformer::getLegalRotations() {
  LinkedList<String> result;
  
  result.add("rotateLeft");
  result.add("rotateRight");
  result.add("rotateFront");
  result.add("rotateBack");
  
  return result;
}

void PlaneTopTransformer::rotateUp(int delayTime) {}
void PlaneTopTransformer::rotateDown(int delayTime) {}

void PlaneTopTransformer::rotateLeft(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneXZ03, planeX,
                            new PlaneLeftTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneTopTransformer::rotateRight(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneXZ00, planeX,
                            new PlaneRightTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneTopTransformer::rotateFront(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneYZ03, planeY,
                            new PlaneFrontTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneTopTransformer::rotateBack(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneYZ00, planeY,
                            new PlaneBackTransformer(plane),
                            plane->offset, delayTime);
}

LinkedList<Led>* PlaneTopTransformer::getLeds() {
  LinkedList<Led>* leds = new LinkedList<Led>();
  
  for (byte x = 0; x < CUBESIZE; x++) {
    for (byte y = 0; y < CUBESIZE; y++) {
      leds->add(Led (Position(x,y, plane->offset), true));
    }
  }
  
  return leds;
}

xyz PlaneTopTransformer::getDirection() {
  return Direction::down;
}

PlaneTransformer* PlaneTopTransformer::getOppositePlaneTransformer() {
  return new PlaneBotTransformer(plane);
}

// Plane Bot //

PlaneBotTransformer::PlaneBotTransformer(Plane* planeRef) : PlaneTransformer(planeRef) {}

LinkedList<String> PlaneBotTransformer::getLegalRotations() {
  LinkedList<String> result;
  
  result.add("rotateLeft");
  result.add("rotateRight");
  result.add("rotateFront");
  result.add("rotateBack");
  
  return result;
}

void PlaneBotTransformer::rotateUp(int delayTime){}
void PlaneBotTransformer::rotateDown(int delayTime){}

void PlaneBotTransformer::rotateLeft(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneXZ00, planeX,
                            new PlaneLeftTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneBotTransformer::rotateRight(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneXZ03, planeX,
                            new PlaneRightTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneBotTransformer::rotateFront(int delayTime) {
  PlaneTransformer::rotate(planeZ, diagonalPlaneYZ00, planeY,
                            new PlaneFrontTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneBotTransformer::rotateBack(int delayTime) {  
  PlaneTransformer::rotate(planeZ, diagonalPlaneYZ03, planeY,
                            new PlaneBackTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

LinkedList<Led>* PlaneBotTransformer::getLeds() {
  LinkedList<Led>* leds = new LinkedList<Led>();
  
  for (byte x = 0; x < CUBESIZE; x++) {
    for (byte y = 0; y < CUBESIZE; y++) {
      leds->add(Led (Position(x,y, plane->offset), true));
    }
  }
  
  return leds;
}

xyz PlaneBotTransformer::getDirection() {
  return Direction::up;
}

PlaneTransformer* PlaneBotTransformer::getOppositePlaneTransformer() {
  return new PlaneTopTransformer(plane);
}

// Plane Left //

PlaneLeftTransformer::PlaneLeftTransformer(Plane* planeRef) : PlaneTransformer(planeRef) {}

LinkedList<String> PlaneLeftTransformer::getLegalRotations() {
  LinkedList<String> result;
  
  result.add("rotateUp");
  result.add("rotateDown");
  result.add("rotateFront");
  result.add("rotateBack");
  
  return result;
}

void PlaneLeftTransformer::rotateLeft(int delayTime) {}
void PlaneLeftTransformer::rotateRight(int delayTime) {}

void PlaneLeftTransformer::rotateUp(int delayTime){  
  PlaneTransformer::rotate(planeX, diagonalPlaneXZ03, planeZ,
                            new PlaneTopTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneLeftTransformer::rotateDown(int delayTime){
  PlaneTransformer::rotate(planeX, diagonalPlaneXZ00, planeZ,
                            new PlaneBotTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneLeftTransformer::rotateFront(int delayTime) {
  PlaneTransformer::rotate(planeX, diagonalPlaneXY00, planeY,
                            new PlaneFrontTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneLeftTransformer::rotateBack(int delayTime) {
  PlaneTransformer::rotate(planeX, diagonalPlaneXY03, planeY,
                            new PlaneBackTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

LinkedList<Led>* PlaneLeftTransformer::getLeds() {
  LinkedList<Led>* leds = new LinkedList<Led>();
  
  for (byte y = 0; y < CUBESIZE; y++) {
    for (byte z = 0; z < CUBESIZE; z++) {
      leds->add(Led (Position(plane->offset, y,z), true));
    }
  }
  
  return leds;
}

xyz PlaneLeftTransformer::getDirection() {
  return Direction::rght;
}

PlaneTransformer* PlaneLeftTransformer::getOppositePlaneTransformer() {
  return new PlaneRightTransformer(plane);
}

// Plane Right //

PlaneRightTransformer::PlaneRightTransformer(Plane* planeRef) : PlaneTransformer(planeRef) {}

LinkedList<String> PlaneRightTransformer::getLegalRotations() {
  LinkedList<String> result;
  
  result.add("rotateUp");
  result.add("rotateDown");
  result.add("rotateFront");
  result.add("rotateBack");
  
  return result;
}

void PlaneRightTransformer::rotateLeft(int delayTime) {}
void PlaneRightTransformer::rotateRight(int delayTime) {}

void PlaneRightTransformer::rotateUp(int delayTime){  
  PlaneTransformer::rotate(planeX, diagonalPlaneXZ00, planeZ,
                            new PlaneTopTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneRightTransformer::rotateDown(int delayTime){
  PlaneTransformer::rotate(planeX, diagonalPlaneXZ03, planeZ,
                            new PlaneBotTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneRightTransformer::rotateFront(int delayTime) {
  PlaneTransformer::rotate(planeX, diagonalPlaneXY03, planeY,
                            new PlaneFrontTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneRightTransformer::rotateBack(int delayTime) {
  PlaneTransformer::rotate(planeX, diagonalPlaneXY00, planeY,
                            new PlaneBackTransformer(plane),
                            plane->offset, delayTime);
}

LinkedList<Led>* PlaneRightTransformer::getLeds() {
  LinkedList<Led>* leds = new LinkedList<Led>();
  
  for (byte y = 0; y < CUBESIZE; y++) {
    for (byte z = 0; z < CUBESIZE; z++) {
      leds->add(Led (Position(plane->offset, y,z), true));
    }
  }
  
  return leds;
}

xyz PlaneRightTransformer::getDirection() {
  return Direction::lft;
}

PlaneTransformer* PlaneRightTransformer::getOppositePlaneTransformer() {
  return new PlaneLeftTransformer(plane);
}

// Plane Front //

PlaneFrontTransformer::PlaneFrontTransformer(Plane* planeRef) : PlaneTransformer(planeRef) {}

LinkedList<String> PlaneFrontTransformer::getLegalRotations() {
  LinkedList<String> result;
  
  result.add("rotateUp");
  result.add("rotateDown");
  result.add("rotateLeft");
  result.add("rotateRight");
  
  return result;
}

void PlaneFrontTransformer::rotateFront(int delayTime) {}
void PlaneFrontTransformer::rotateBack(int delayTime) {}

void PlaneFrontTransformer::rotateUp(int delayTime){  
  PlaneTransformer::rotate(planeY, diagonalPlaneYZ03, planeZ,
                            new PlaneTopTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneFrontTransformer::rotateDown(int delayTime){
  PlaneTransformer::rotate(planeY, diagonalPlaneYZ00, planeZ,
                            new PlaneBotTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneFrontTransformer::rotateLeft(int delayTime) {
  PlaneTransformer::rotate(planeY, diagonalPlaneXY00, planeX,
                            new PlaneLeftTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneFrontTransformer::rotateRight(int delayTime) {
  PlaneTransformer::rotate(planeY, diagonalPlaneXY03, planeX,
                            new PlaneRightTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

LinkedList<Led>* PlaneFrontTransformer::getLeds() {
  LinkedList<Led>* leds = new LinkedList<Led>();
  
  for (byte x = 0; x < CUBESIZE; x++) {
    for (byte z = 0; z < CUBESIZE; z++) {
      leds->add(Led (Position(x, plane->offset, z), true));
    }
  }
  
  return leds;
}

xyz PlaneFrontTransformer::getDirection() {
  return Direction::back;
}

PlaneTransformer* PlaneFrontTransformer::getOppositePlaneTransformer() {
  return new PlaneBackTransformer(plane);
}

// Plane Back //

PlaneBackTransformer::PlaneBackTransformer(Plane* planeRef) : PlaneTransformer(planeRef) {}

LinkedList<String> PlaneBackTransformer::getLegalRotations() {
  LinkedList<String> result;
  
  result.add("rotateUp");
  result.add("rotateDown");
  result.add("rotateLeft");
  result.add("rotateRight");
  
  return result;
}

void PlaneBackTransformer::rotateFront(int delayTime) {}
void PlaneBackTransformer::rotateBack(int delayTime) {}

void PlaneBackTransformer::rotateUp(int delayTime){  
  PlaneTransformer::rotate(planeY, diagonalPlaneYZ00, planeZ,
                            new PlaneTopTransformer(plane),
                            plane->offset, delayTime);
}

void PlaneBackTransformer::rotateDown(int delayTime){
  PlaneTransformer::rotate(planeY, diagonalPlaneYZ03, planeZ,
                            new PlaneBotTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneBackTransformer::rotateLeft(int delayTime) {
  PlaneTransformer::rotate(planeY, diagonalPlaneXY03, planeX,
                            new PlaneLeftTransformer(plane),
                            CUBESIZE-1 - plane->offset, delayTime);
}

void PlaneBackTransformer::rotateRight(int delayTime) {
  PlaneTransformer::rotate(planeY, diagonalPlaneXY00, planeX,
                            new PlaneRightTransformer(plane),
                            plane->offset, delayTime);
}

LinkedList<Led>* PlaneBackTransformer::getLeds() {
  LinkedList<Led>* leds = new LinkedList<Led>();
  
  for (byte x = 0; x < CUBESIZE; x++) {
    for (byte z = 0; z < CUBESIZE; z++) {
      leds->add(Led (Position(x, plane->offset, z), true));
    }
  }
  
  return leds;
}

xyz PlaneBackTransformer::getDirection() {
  return Direction::fwd;
}

PlaneTransformer* PlaneBackTransformer::getOppositePlaneTransformer() {
  return new PlaneFrontTransformer(plane);
}
