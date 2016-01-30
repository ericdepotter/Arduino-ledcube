#include "Delay.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

void NonBlockDelay::delay (unsigned long t)
{
  iTimeout = millis() + t;
  return;
};
bool NonBlockDelay::timeout (void)
{
  return (iTimeout < millis());
}
unsigned long NonBlockDelay::time(void)
 {
   return iTimeout;
 }


