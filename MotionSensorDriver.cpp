#include <Arduino.h>
#include "MotionSensorDriver.h"
#include <math.h>

#define ULTRASONIC_TRIG_PRE_SIGNAL_SILENSE                (3)     // in us
#define ULTRASONIC_TRIG_SIGNAL_DURATION                   (10)    // in us

#define SPEED_OF_SOUND                                    (343.216)   // m/s (mm/ms) @ 25 degC 
#define ULTRASONIC_MAX_DISTANCE                           UltrasonicMotionSensorDriver::DEF_MAX_DISTANCE

UltrasonicMotionSensorDriver::UltrasonicMotionSensorDriver(int trigPin, int echoPin, int maxDistance)
{
  this->durationToTravel1mm = 2 * 1000 / SPEED_OF_SOUND; // in us/mm, 2 for travel both direction 
  
  this->trigPin         = trigPin;
  this->echoPin         = echoPin;
  this->maxDistance     = ULTRASONIC_MAX_DISTANCE;
  this->timeOut         = ULTRASONIC_MAX_DISTANCE * durationToTravel1mm; 
  this->maxDistance     = maxDistance;
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

#define INFRARED_MAX_DISTANCE                             (1500)

InfraredMotionSensorDriver::InfraredMotionSensorDriver(int analogPin, int maxDistance)
{
  this->analogPin   = analogPin;
  this->maxDistance = maxDistance;
}

void InfraredMotionSensorDriver::setup()
{
  maxDistance = INFRARED_MAX_DISTANCE;
}

int InfraredMotionSensorDriver::mesureDistance()
{ 
  // returns distance in mm 
  int duration = analogRead(analogPin);

  //double buf = duration * 5 / 1024.0;
  //int distance = 61.681 * pow(buf, -1.133) * 10;    // one of the variants for define distance

  //int distance = 1735 * pow(duration, -1.07) * 100; // better for define distance

  int distance = duration;                            // return V instead mm(hack)
  
  return (distance);
}
 
