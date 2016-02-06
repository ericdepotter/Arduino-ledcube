#include "movingPlane.h"

void movingPlane(int time, int drawTime) {
  emptyCube();

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

  delete plane;
}