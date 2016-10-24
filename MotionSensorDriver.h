#ifndef __MOTION_SENSOR_DRIVER_H__
#define __MOTION_SENSOR_DRIVER_H__

// Motion Sensor Driver
// ---------------------------

class MotionSensorDriver
{
  public:

  enum
  {
    DISTANCE_UNKNOWN = -1,
  };
  
  protected:

  int    trigPin;
  int    echoPin;
  int    timeOut;
  int    maxDistance;
  double durationToTravel1mm;
  
  public:

  MotionSensorDriver(int trigPin, int echoPin);
  void setup();

  int  mesureDistance();
};

#endif // __MOTION_SENSOR_DRIVER_H__

