//=================================
// include guard
#ifndef __SNAKE_H_INCLUDED__
#define __SNAKE_H_INCLUDED__

#include "cube.h"
#include "Delay.h"
#include "pos.h"

void snakeEffect(int, int = 400);

class Snake {
  public:
    Snake(byte, byte);
    Snake(byte, byte, xyz);
    Snake(byte, byte, xyz, xyz);
    
    void update();

  protected:
    xyz nextPart();

  private:
    byte length;
    byte turnChance;
    xyz direction;
    
    xyz* snakeParts;
    byte headIndex;
    
    void init(byte, byte, xyz, xyz);
};

#endif
