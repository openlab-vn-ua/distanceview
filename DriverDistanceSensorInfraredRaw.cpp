#include <Arduino.h>
#include "DriverDistanceSensorInfraredRaw.h"

#define INFRARED_MAX_DISTANCE                             (1500)

DriverDistanceSensorInfraredRaw::DriverDistanceSensorInfraredRaw(int analogPin)
{
  this->analogPin = analogPin;
}

void DriverDistanceSensorInfraredRaw::setup()
{
  maxDistance = INFRARED_MAX_DISTANCE;
}

int DriverDistanceSensorInfraredRaw::mesureDistance()
{ 
  // returns distance in V
  int duration = analogRead(analogPin);

  return (duration);
}
 
