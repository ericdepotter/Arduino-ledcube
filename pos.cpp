#include "pos.h"
    
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
