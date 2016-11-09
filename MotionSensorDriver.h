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

  enum
  {
    MIN_DISTANCE = 0, // in mm
    MAX_DISTANCE = 4000, // in mm
  };

  enum
  {
    DEF_MAX_DISTANCE = MAX_DISTANCE // in mm
  };

  UltrasonicMotionSensorDriver(int trigPin, int echoPin, int maxDistance = DEF_MAX_DISTANCE);

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

  enum
  {
    MIN_DISTANCE = 200,
    MAX_DISTANCE = 1200,
  };

  enum
  {
    DEF_MAX_DISTANCE = MAX_DISTANCE // in mm
  };

  InfraredMotionSensorDriver(int analogPin, int maxDistance = DEF_MAX_DISTANCE);

  virtual
  void setup();
  
  virtual
  int  mesureDistance();
};

class InfraredMotionSensorDriverRaw : public MotionSensorDriver
{
  protected:
    
  int    analogPin;
  int    maxDistance;
  
  public:

  InfraredMotionSensorDriverRaw(int analogPin);

  virtual
  void setup();
  
  virtual
  int  mesureDistance();
};

#endif // __MOTION_SENSOR_DRIVER_H__

