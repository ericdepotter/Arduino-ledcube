#include "snake.h"

void snakeEffect(int time, int drawTime) {
  emptyCube();
  
  //Snake* snake1 = new Snake(5, 0);
  Snake* snake2 = new Snake(6, 25);

  drawState(drawTime);

  NonBlockDelay timer;
  timer.delay(time);

  while(!timer.timeout()) {
    //snake1->update();
    snake2->update();

    drawState(drawTime);
  }

  //delete snake1;
  delete snake2;
}

/***************
 * Snake class *
 ***************/

Snake::Snake(byte length, byte turnChance) {
  xyz startPos = randomPosition();
  init(length, turnChance, startPos, randomValidDirection(startPos));
}

Snake::Snake(byte length, byte turnChance, xyz startPos) {
  init(length, turnChance, startPos, randomValidDirection(startPos));  
}

Snake::Snake(byte length, byte turnChance, xyz startPos, xyz dir) {
  init(length, turnChance, startPos, dir);
}

void Snake::init(byte length, byte turnChance, xyz startPos, xyz dir) {
  this->length = length;
  this->turnChance = turnChance;
  direction = dir;

  snakeParts = new xyz[length];
  for (byte idx = 0; idx < length; idx++) {
    snakeParts[idx] = {-1, -1, -1};
  }
  
  snakeParts[0] = startPos;
  headIndex = 0;
}

void Snake::update() {
  byte nextIndex = (headIndex + 1) % length;

  //Serial.print("nextIndex: ");
 // Serial.println(nextIndex);

  // Turn off the tail
  xyz tail = snakeParts[nextIndex];
  ledOff(tail.x, tail.y, tail.z);

  // Replace the tail with the head and turn it on
  xyz next = nextPart();
  snakeParts[nextIndex] = next;
  ledOn(next.x, next.y, next.z);

  headIndex = nextIndex;
}

xyz Snake::nextPart() {
  xyz head = snakeParts[headIndex];
  xyz moved = head + direction;
  
  if ( !inRange(moved.x, moved.y, moved.z) || (random(100) < turnChance) ) {
    direction = randomValidDirection(head, direction.negate());
    return head + direction;
  }
   
  return moved;
}

