//=================================
// include guard
#ifndef __POS_H_INCLUDED__
#define __POS_H_INCLUDED__

#include <stdint.h>;
 
#define byte uint8_t

struct xyz {
  byte x;
  byte y;
  byte z;
  
  bool operator == (const xyz v1) const {
    return ( x == v1.x && y == v1.y && z == v1.z );
  }

  xyz operator - (const xyz v1) const {
    xyz diff = { x - v1.x, y - v1.y, z - v1.z };
    return diff;
  }
};

namespace Direction {
  const xyz fwd  = {0,-1,0};
  const xyz back = {0,1,0};
  
  const xyz lft  = {-1,0,0};
  const xyz rght = {1,0,0};
  
  const xyz up   = {0,0,1};
  const xyz down = {0,0,-1};
}

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

#endif
