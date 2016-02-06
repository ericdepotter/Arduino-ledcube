//=================================
// include guard
#ifndef __WAVESINE_H_INCLUDED__
#define __WAVESINE_H_INCLUDED__

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Delay.h"
#include "led.h"
#include "pos.h"
#include "cube.h"

void waveSine(int, int = 200);

#endif
