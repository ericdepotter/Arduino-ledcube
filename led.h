//=================================
// include guard
#ifndef __LED_H_INCLUDED__
#define __LED_H_INCLUDED__

#include "pos.h";
#include "cube.h";

class Led {
  public:
    Led();
    Led(xyz, bool);
    Led(Position, bool);
  
    Position getPosition();
    bool atEdgeOfCube();
    
    bool canMove(xyz);
    bool canMove(Position);
    Position move(xyz);
    Position move(Position);
    Position moveSafe(xyz);
    Position moveSafe(Position);
    
    bool getState();
    void setState(bool);
  protected:
    Position position;
    bool state;
  private:
    void init(Position, bool);
};

class AlternatingLed: public Led {
  public:
    AlternatingLed();
    AlternatingLed(xyz, bool, xyz, xyz, xyz);
    
    Position update();
  private:
    xyz direction;
    xyz min;
    xyz max;
};

#endif
