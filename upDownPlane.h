//=================================
// include guard
#ifndef __UPDOWNPLANE_H_INCLUDED__
#define __UPDOWNPLANE_H_INCLUDED__

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "cube.h"
#include "Delay.h"
#include "led.h"
#include "pos.h"

void upDownPlane(int, int = 200);

#endif
