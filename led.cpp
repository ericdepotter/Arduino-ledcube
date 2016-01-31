#include "led.h"

// Constructors //
Led::Led() {
  init(Position(-1,-1,-1), false);
}

Led::Led(xyz pos, bool on) {
  init(Position(pos), on);
}

Led::Led(Position pos, bool on) {
  init(pos, on);
}

void Led::init(Position pos, bool on) {
  position = pos;
  state = on;

  led(pos.getX(), pos.getY(), pos.getZ(), on);
}

// Getters and setters //

Position Led::getPosition() {
  return position;
}

bool Led::atEdgeOfCube() {
  byte x = position.getX();
  byte y = position.getY();
  byte z = position.getZ();
  
  return (x == 0 || x == CUBESIZE-1) ||
         (y == 0 || y == CUBESIZE-1) ||
         (z == 0 || z == CUBESIZE-1);
}


bool Led::getState() {
  return state;
}

void Led::setState(bool newState) {
  state = newState;
  led(position.getX(), position.getY(), position.getZ(), newState);
}

// Move //

bool Led::canMove(xyz delta) {
  Position deltaPos = position.addPos(delta);
  
  return inRange(deltaPos.getX(), deltaPos.getY(), deltaPos.getZ());
}

bool Led::canMove(Position delta) {
  return canMove(delta.getPos());
}

/* Move the led with delta and return the new position. */
Position Led::move(xyz delta) {
  // set led at current position to the opposite state of this led
  led(position.getX(), position.getY(), position.getZ(), !state);
  // move the position of this led
  position = position.addPos(delta);
  // set led at new position to the state of this led
  led(position.getX(), position.getY(), position.getZ(), state);
  
  return position;
}

/* Move the led with delta and return the new position. */
Position Led::move(Position delta) {
  return move(delta.getPos());
}

/* Move the led with delta, if the new position is a valid position and return the new position. */
Position Led::moveSafe(xyz delta) {
  if (canMove(delta))
    return move(delta);
  
  return position;
}

/* Move the led with delta, if the new position is a valid position and return the new position. */
Position Led::moveSafe(Position delta) {
  return moveSafe(delta.getPos());
}



/******************
** AlternatingLed *
******************/

AlternatingLed::AlternatingLed(xyz pos, bool on, xyz dir, xyz minv, xyz maxv) : Led(pos, on) {
  direction = dir;
  min = minv;
  max = maxv;

  xyz moved = pos + dir;  
  if ( (moved.x > maxv.x || moved.y > maxv.y || moved.z > maxv.z) ||
       (moved.x < minv.x || moved.y < minv.y || moved.z < minv.z) ) {
    direction = direction.negate();
  }
}

Position AlternatingLed::update() {
  Led::move(direction);
  
  if (position.getPos() == min || position.getPos() == max) {
    direction = direction.negate();
  }
  
  return position;
}
