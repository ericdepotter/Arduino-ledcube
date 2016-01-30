//=================================
// include guard
#ifndef __PLANE_H_INCLUDED__
#define __PLANE_H_INCLUDED__

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DELAYTIME 200

#include "LinkedList.h";
#include "led.h";
#include "cube.h";

typedef void (*planeCallback)(byte, bool);
typedef void (*diagonalCallback)(bool);

enum Axis{X, Y, Z};

class Plane;

class PlaneTransformer {
  protected:
    Plane* plane;
    
    PlaneTransformer(Plane*);
    
    virtual LinkedList<Led>* getLeds() = 0;
    virtual xyz getDirection() = 0;
    virtual PlaneTransformer* getOppositePlaneTransformer() = 0;
    
    void rotate(planeCallback, diagonalCallback, planeCallback, PlaneTransformer*, byte, int);
  public:
    void sendPlane(int = DELAYTIME);
    void sendPlaneDiffuse(int = DELAYTIME);
  
    virtual LinkedList<String> getLegalRotations() = 0;
    
    virtual void rotateUp(int = DELAYTIME) = 0;
    virtual void rotateDown(int = DELAYTIME) = 0;
    virtual void rotateLeft(int = DELAYTIME) = 0;
    virtual void rotateRight(int = DELAYTIME) = 0;
    virtual void rotateFront(int = DELAYTIME) = 0;
    virtual void rotateBack(int = DELAYTIME) = 0;
};

class Plane {
  public:
    LinkedList<String> getLegalRotations() { return transformer->getLegalRotations(); };
    
    void sendPlane(int drawTime = DELAYTIME) { transformer->sendPlane(drawTime); };
    void sendPlaneDiffuse(int drawTime = DELAYTIME) { transformer->sendPlaneDiffuse(drawTime); };
    
    virtual void rotateUp(int = DELAYTIME) = 0;
    virtual void rotateDown(int = DELAYTIME) = 0;
    virtual void rotateLeft(int = DELAYTIME) = 0;
    virtual void rotateRight(int = DELAYTIME) = 0;
    virtual void rotateFront(int = DELAYTIME) = 0;
    virtual void rotateBack(int = DELAYTIME) = 0;
  protected:   
    byte offset;
    
    PlaneTransformer* transformer;
  private:
    void setTransformer(PlaneTransformer* newTransformer) {
      delete transformer;
      transformer = newTransformer;
    }
  
    friend class PlaneTransformer;
    friend class PlaneTopTransformer;
    friend class PlaneBotTransformer;
    friend class PlaneLeftTransformer;
    friend class PlaneRightTransformer;
    friend class PlaneFrontTransformer;
    friend class PlaneBackTransformer;
};

class NormalPlane : public Plane {
  public:
    NormalPlane(Axis, byte);
    
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
};

//class InverseTransformPlane : public Plane {
//  private:
//    Plane* plane;
//  public:
//    InverseTransformPlane(Axis, int);
//    InverseTransformPlane(Plane*);
//    
//    void rotateUp(int = DELAYTIME);
//    void rotateDown(int = DELAYTIME);
//    void rotateLeft(int = DELAYTIME);
//    void rotateRight(int = DELAYTIME);
//    void rotateFront(int = DELAYTIME);
//    void rotateBack(int = DELAYTIME);
//};

/*********************
** PlaneTransformer **
*********************/

class PlaneTopTransformer : public PlaneTransformer {
  public:
    PlaneTopTransformer(Plane*);
    
    LinkedList<String> getLegalRotations();
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
  protected:
    LinkedList<Led>* getLeds();
    xyz getDirection();
    PlaneTransformer* getOppositePlaneTransformer();
};
class PlaneBotTransformer : public PlaneTransformer {
  public:
    PlaneBotTransformer(Plane*);
    
    LinkedList<String> getLegalRotations();
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
  protected:
    LinkedList<Led>* getLeds();
    xyz getDirection();
    PlaneTransformer* getOppositePlaneTransformer();
};
class PlaneLeftTransformer : public PlaneTransformer {
  public:
    PlaneLeftTransformer(Plane*);
    
    LinkedList<String> getLegalRotations();
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
  protected:
    LinkedList<Led>* getLeds();
    xyz getDirection();
    PlaneTransformer* getOppositePlaneTransformer();
};
class PlaneRightTransformer : public PlaneTransformer {
  public:
    PlaneRightTransformer(Plane*);
    
    LinkedList<String> getLegalRotations();
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
  protected:
    LinkedList<Led>* getLeds();
    xyz getDirection();
    PlaneTransformer* getOppositePlaneTransformer();
};
class PlaneFrontTransformer : public PlaneTransformer {
  public:
    PlaneFrontTransformer(Plane*);
    
    LinkedList<String> getLegalRotations();
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
  protected:
    LinkedList<Led>* getLeds();
    xyz getDirection();
    PlaneTransformer* getOppositePlaneTransformer();
};
class PlaneBackTransformer : public PlaneTransformer {
  public:
    PlaneBackTransformer(Plane*);
    
    LinkedList<String> getLegalRotations();
    void rotateUp(int = DELAYTIME);
    void rotateDown(int = DELAYTIME);
    void rotateLeft(int = DELAYTIME);
    void rotateRight(int = DELAYTIME);
    void rotateFront(int = DELAYTIME);
    void rotateBack(int = DELAYTIME);
  protected:
    LinkedList<Led>* getLeds();
    xyz getDirection();
    PlaneTransformer* getOppositePlaneTransformer();
};
#endif
