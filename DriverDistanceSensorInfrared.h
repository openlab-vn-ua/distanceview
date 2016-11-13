#ifndef __DRIVER_MOTION_SENSOR_INFRARED_H__
#define __DRIVER_MOTION_SENSOR_INFRARED_H__

#include "DriverDistanceSensor.h"

// Driver Distance Sensor Infrared
// ---------------------------

class DriverDistanceSensorInfrared : public DriverDistanceSensor
{
  protected:
    
   int          analogPin;
   int          maxDistance;
  
  public:

   DriverDistanceSensorInfrared(int analogPin);

   virtual void setup();
  
   virtual int  mesureDistance();
};

#endif // __DRIVER_MOTION_SENSOR_INFRARED_H__

