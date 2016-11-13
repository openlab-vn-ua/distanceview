#ifndef __DRIVER_MOTION_SENSOR_H__
#define __DRIVER_MOTION_SENSOR_H__

// Driver Distance Sensor 
// ---------------------------

class DriverDistanceSensor
{
  public:
  
   enum
   {
     DISTANCE_UNKNOWN = -1,
   };
  
  public:

   virtual void setup() {};

   virtual int  mesureDistance() = 0;
};

#endif //  __DRIVER_MOTION_SENSOR_H__

