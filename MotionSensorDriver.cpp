#include <Arduino.h>
#include "MotionSensorDriver.h"

#define ULTRASONIC_TRIG_PRE_SIGNAL_SILENSE                (3)     // in us
#define ULTRASONIC_TRIG_SIGNAL_DURATION                   (10)    // in us

#define SPEED_OF_SOUND                                    (343.216)   // m/s (mm/ms) @ 25 degC 
#define ULTRASONIC_MAX_DISTANCE                           (4000)
#define INFRARED_MAX_DISTANCE                             (1500)

UltrasonicMotionSensorDriver::UltrasonicMotionSensorDriver(int trigPin, int echoPin)
{
  this->durationToTravel1mm = 2 * 1000 / SPEED_OF_SOUND; // in us/mm, 2 for travel both direction 
  
  this->trigPin         = trigPin;
  this->echoPin         = echoPin;
  this->maxDistance     = ULTRASONIC_MAX_DISTANCE;
  this->timeOut         = ULTRASONIC_MAX_DISTANCE * durationToTravel1mm; 
}

void UltrasonicMotionSensorDriver::setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int UltrasonicMotionSensorDriver::mesureDistance()
{ 
  // returns distance in mm 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(ULTRASONIC_TRIG_PRE_SIGNAL_SILENSE);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(ULTRASONIC_TRIG_SIGNAL_DURATION);
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

InfraredMotionSensorDriver::InfraredMotionSensorDriver(int analogPin)
{
  this->analogPin = analogPin;
}

void InfraredMotionSensorDriver::setup()
{
  maxDistance = INFRARED_MAX_DISTANCE;
}

int InfraredMotionSensorDriver::mesureDistance()
{ 
  // returns distance in mm 
  int duration = analogRead(analogPin);
  
  int distance = 94620 / (duration - 16.92);

  if (duration <= 16.92)
  {
    return (DISTANCE_UNKNOWN);
  }
  else
  {
    return (distance);
  }
}
 
