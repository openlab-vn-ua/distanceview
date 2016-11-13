#ifndef __MOTION_SENSOR_DRIVER_ULTRASONIC_H__
#define __MOTION_SENSOR_DRIVER_ULTRASONIC_H__

#include "DriverDistanceSensor.h"

// Distance Sensor Driver Ultrasonic
// ---------------------------

class DriverDistanceSensorUltrasonic : public DriverDistanceSensor
{
  protected:

   int          trigPin;
   int          echoPin;
   int          timeOut;
   double       durationToTravel1mm;
   int          maxDistance;

  public:

   DriverDistanceSensorUltrasonic(int trigPin, int echoPin);

   virtual void setup();
  
   virtual int  mesureDistance();
};

#endif // __MOTION_SENSOR_DRIVER_ULTRASONIC_H__

