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
  
  public:

  virtual
  void setup() {};

  virtual
  int  mesureDistance() = 0;
};

class UltrasonicMotionSensorDriver : public MotionSensorDriver
{
  protected:

  int    trigPin;
  int    echoPin;
  int    timeOut;
  double durationToTravel1mm;
  int    maxDistance;

  public:

  UltrasonicMotionSensorDriver(int trigPin, int echoPin);

  virtual
  void setup();
  
  virtual
  int  mesureDistance();
};

class InfraredMotionSensorDriver : public MotionSensorDriver
{
  protected:
    
  int    analogPin;
  int    maxDistance;
  
  public:

  InfraredMotionSensorDriver(int analogPin);

  virtual
  void setup();
  
  virtual
  int  mesureDistance();
};

#endif // __MOTION_SENSOR_DRIVER_H__

