#include "pos.h"

xyz* allDirections() {
  xyz* directions = new xyz[NUMBER_DIRECTIONS];
  byte index = 0;

  directions[index++] = Direction::forward;
  directions[index++] = Direction::back;
  directions[index++] = Direction::left;
  directions[index++] = Direction::right;
  directions[index++] = Direction::up;
  directions[index++] = Direction::down;

  /*directions[index++] = Direction::forward + Direction::left;
  directions[index++] = Direction::forward + Direction::right;
  directions[index++] = Direction::forward + Direction::up;
  directions[index++] = Direction::forward + Direction::down;

  directions[index++] = Direction::back + Direction::left;
  directions[index++] = Direction::back + Direction::right;
  directions[index++] = Direction::back + Direction::up;
  directions[index++] = Direction::back + Direction::down;

  directions[index++] = Direction::left + Direction::up;
  directions[index++] = Direction::left + Direction::down;

  directions[index++] = Direction::right + Direction::up;
  directions[index++] = Direction::right + Direction::down;

  directions[index++] = Direction::forward + Direction::left + Direction::up;
  directions[index++] = Direction::forward + Direction::left + Direction::down;
  directions[index++] = Direction::forward + Direction::right + Direction::up;
  directions[index++] = Direction::forward + Direction::right + Direction::down;

  directions[index++] = Direction::back + Direction::left + Direction::up;
  directions[index++] = Direction::back + Direction::left + Direction::down;
  directions[index++] = Direction::back + Direction::right + Direction::up;
  directions[index++] = Direction::back + Direction::right + Direction::down;*/

  return directions;
}

xyz randomDirection() {
  xyz* allDirs = allDirections();
  xyz dir = allDirs[random(NUMBER_DIRECTIONS)];

  delete allDirs;
  
  return dir;
}

xyz randomValidDirection(xyz pos, xyz ignore) {
  xyz* directions = allDirections();

  xyz dir;
  byte index = random(NUMBER_DIRECTIONS);
  do {
    dir = directions[index++ % NUMBER_DIRECTIONS];
  } while ( !inRange(pos.x + dir.x, pos.y + dir.y, pos.z + dir.z) || dir == ignore );

  delete directions;
  
  return dir;
}

xyz randomPosition() {
  return {random(0, CUBESIZE), random(0, CUBESIZE), random(0, CUBESIZE)};
}
    
/************
** Position *
************/

Position::Position() { 
  init(0, 0, 0);
}

Position::Position(xyz ps) {
  init(ps.x, ps.y, ps.z);
}

Position::Position(byte xv, byte yv, byte zv) {
  init(xv, yv, zv);
}

void Position::init(byte xv, byte yv, byte zv) {
  x = xv;
  y = yv;
  z = zv;
}


byte Position::getX() {
  return x;
}

byte Position::getY() {
  return y;
}

byte Position::getZ() {
  return z;
}

xyz Position::getPos() {
  xyz pos = {x, y, z};
  return pos;
}

/* Adds the given xyz to pos. */
Position Position::addPos(xyz ps) {
  return Position (x + ps.x, y + ps.y, z + ps.z);
}

Position Position::addPos(Position ps) {
  return addPos(ps.getPos());
}
