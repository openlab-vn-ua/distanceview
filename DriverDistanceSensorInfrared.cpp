#include <Arduino.h>
#include "DriverDistanceSensorInfrared.h"

#define INFRARED_MAX_DISTANCE                             (1500)

DriverDistanceSensorInfrared::DriverDistanceSensorInfrared(int analogPin)
{
  this->analogPin = analogPin;
}

void DriverDistanceSensorInfrared::setup()
{
  maxDistance = INFRARED_MAX_DISTANCE;
}

int DriverDistanceSensorInfrared::mesureDistance()
{ 
  // returns distance in mm 
  int duration = analogRead(analogPin);
  
  int distance = 1735 * pow(duration, -1.07) * 100;

  if (distance <= 20)
  {
    return (DISTANCE_UNKNOWN);
  }
  else
  {
    return (distance);
  }
}
 
