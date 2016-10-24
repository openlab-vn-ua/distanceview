#include <Arduino.h>
#include "MotionSensorDriver.h"

#define TRIG_PRE_SIGNAL_SILENSE                (3)     // in us
#define TRIG_SIGNAL_DURATION                   (10)    // in us

#define SPEED_OF_SOUND                         (343.216)   // m/s @ 25 degC
#define MAX_DISTANCE                           (4000)
//#define DURATION_TO_TRAVEL_1MM               (5.8)   // (5.8) number of us to travel 1mm

MotionSensorDriver::MotionSensorDriver(int trigPin, int echoPin)
{
  durationToTravel1mm   = 2000 / SPEED_OF_SOUND;
  
  this->trigPin         = trigPin;
  this->echoPin         = echoPin;
  this->maxDistance     = MAX_DISTANCE;
  this->timeOut         = MAX_DISTANCE * durationToTravel1mm; 
}

void MotionSensorDriver::setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int MotionSensorDriver::mesureDistance()
{ 
  // returns distance in mm 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(TRIG_PRE_SIGNAL_SILENSE);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(TRIG_SIGNAL_DURATION);
  digitalWrite(trigPin, LOW);

  int duration;
  if (maxDistance != DISTANCE_UNKNOWN)
  {
    duration = pulseIn(echoPin, HIGH, timeOut);
  }
  else
  {
    duration = pulseIn(echoPin, HIGH);
  }
  
  int distance = duration / durationToTravel1mm;

  if (duration == 0)
  {
    return (DISTANCE_UNKNOWN);
  }
  else
  {
    return (distance);
  }
}

 
