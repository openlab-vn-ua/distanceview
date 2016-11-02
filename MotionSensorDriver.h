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

    int    maxDistance;
  
  public:

    virtual
    void setup()  {};

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

  public:

    UltrasonicMotionSensorDriver(int trigPin, int echoPin);
    void setup();
    int  mesureDistance();
};

class InfraredMotionSensorDriver : public MotionSensorDriver
{
  protected:
    
    int analogPin;
  
  public:

    InfraredMotionSensorDriver(int analogPin);
    void setup();
    int  mesureDistance();
};

#endif // __MOTION_SENSOR_DRIVER_H__

