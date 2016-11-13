#ifndef __MOTION_SENSOR_DRIVER_INFRARED_RAW_H__
#define __MOTION_SENSOR_DRIVER_INFRARED_RAW_H__

#include "DriverDistanceSensor.h"

// Distance Sensor Driver Infrared Raw
// ---------------------------

class DriverDistanceSensorInfraredRaw : public DriverDistanceSensor
{
  protected:
    
   int          analogPin;
   int          maxDistance;
  
  public:

   DriverDistanceSensorInfraredRaw(int analogPin);

   virtual void setup();
  
   virtual int  mesureDistance();
};

#endif // __MOTION_SENSOR_DRIVER_INFRARED_RAW_H__

