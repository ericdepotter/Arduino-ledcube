//=================================
// include guard
#ifndef __POS_H_INCLUDED__
#define __POS_H_INCLUDED__

#include <stdint.h>
#include "cube.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
 
#define byte uint8_t
//#define NUMBER_DIRECTIONS 26
#define NUMBER_DIRECTIONS 6

struct xyz {
  byte x;
  byte y;
  byte z;
  
  bool operator == (const xyz v1) const {
    return ( x == v1.x && y == v1.y && z == v1.z );
  }

  xyz operator - (const xyz v1) const {
    return { x - v1.x, y - v1.y, z - v1.z };
  }

  xyz operator + (const xyz v1) const {
    return { x + v1.x, y + v1.y, z + v1.z };
  }

  xyz negate() const {
    return { -x, -y, -z };
  }
};

namespace Direction {
  const xyz forward  = {0,-1,0};
  const xyz back     = {0,1,0};
  
  const xyz left     = {-1,0,0};
  const xyz right    = {1,0,0};
  
  const xyz up       = {0,0,1};
  const xyz down     = {0,0,-1};
}

xyz* allDirections();

xyz randomDirection();
xyz randomValidDirection(xyz, xyz = {5, 5, 5});

class Position {
  public:
    Position();
    Position(xyz);
    Position(byte, byte, byte);
    
    byte getX();
    byte getY();
    byte getZ();
    xyz getPos();
    
    Position addPos(xyz ps);
    Position addPos(Position ps);
  private:
    byte x;
    byte y;
    byte z;
    
    void init(byte, byte, byte);
};

xyz randomPosition();

#endif
