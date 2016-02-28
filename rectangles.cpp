#include "rectangles.h"

/*******************
 * Rectangle Edges *
 *******************/
 
void rectangleEdgesEffect(int drawTime) {  
  emptyCube();
  drawState();
  
  Anchor anchor;
  for(byte i1 = AnchorMax; i1 >= 1; i1--) {
    byte i = i1 - 1;
    anchor = Anchor(i);
    
    for (byte size = CUBESIZE; size >= 1; size--) {
      rectangleEdges(size, anchor, true);
      drawState(drawTime);
      rectangleEdges(size, anchor, false);
    }
    
    for (byte size = 1; size <= CUBESIZE; size++) {
      rectangleEdges(size, anchor, true);
      drawState(drawTime);
      rectangleEdges(size, anchor, false);
    }
  }
  
  rectangleEdges(CUBESIZE, Center, true);
}


void rectangleEdges(byte size, Anchor anchor, bool state) {
  if (size == 0) {
    return;
  }
  
  switch (anchor) {
    case Center: {
      if (size >= (CUBESIZE/2))
        size = (CUBESIZE/2);
      
      byte left = (CUBESIZE/2) - size;
      byte right = (CUBESIZE/2) + size - 1; 
      
      rectangleEdges(Position (left,left,left), Position (right,right,right), state);
      break;
    }
    default: {
      rectangleEdges(size, size, size, anchorPositions[anchor], state);
      break;
    }
  }
}

void rectangleEdges(byte xsize, byte ysize, byte zsize, Position anchor, bool state) {
  xsize -= 1; ysize -= 1; zsize -= 1;
  
  if (anchor.getX() > CUBESIZE/2) {
    xsize = -xsize;
  }
  
  if (anchor.getY() > CUBESIZE/2) {
    ysize = -ysize;
  }
  
  if (anchor.getZ() > CUBESIZE/2) {
    zsize = -zsize;
  }
  
  
  rectangleEdges(anchor, anchor.addPos(Position (xsize, ysize, zsize)), state);
}

void rectangleEdges(Position pos1, Position pos2, bool state) {
  xyz xyz1 = pos1.getPos();
  xyz xyz2 = pos2.getPos();
  
  // horizontal lines
  lineX(xyz1.x, xyz2.x, xyz1.y, xyz1.z, state);
  lineX(xyz1.x, xyz2.x, xyz2.y, xyz1.z, state);
  lineX(xyz1.x, xyz2.x, xyz1.y, xyz2.z, state);
  lineX(xyz1.x, xyz2.x, xyz2.y, xyz2.z, state);
  
  lineY(xyz1.y, xyz2.y, xyz1.x, xyz1.z, state);
  lineY(xyz1.y, xyz2.y, xyz2.x, xyz1.z, state);
  lineY(xyz1.y, xyz2.y, xyz1.x, xyz2.z, state);
  lineY(xyz1.y, xyz2.y, xyz2.x, xyz2.z, state);
  
  // vertical lines
  lineZ(xyz1.z, xyz2.z, xyz1.x, xyz1.y, state);
  lineZ(xyz1.z, xyz2.z, xyz2.x, xyz1.y, state);
  lineZ(xyz1.z, xyz2.z, xyz1.x, xyz2.y, state);
  lineZ(xyz1.z, xyz2.z, xyz2.x, xyz2.y, state);
}
