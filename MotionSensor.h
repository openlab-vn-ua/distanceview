#ifndef __MOTION_SENSOR_H__
#define __MOTION_SENSOR_H__

#include "MotionSensorDriver.h"
#include "Process.h"

// Motion Sensor
// ---------------------------

class MotionSensor;

class MotionSensorHandler
{
  public:

  class Event
  {
    public:

    MotionSensor *source;
  };

  class DistanceUpdatedEvent : public Event
  {
    public:
    
    int           oldDistance; /// DEPRECATED
    int           newDistance;
  };

  virtual
  void onDistanceUpdated(DistanceUpdatedEvent *event) = 0;
};

class MotionSensor : public Process
{
  public:

  enum
  {
    DISTANCE_UNKNOWN = MotionSensorDriver::DISTANCE_UNKNOWN,
  };

  protected:
  
    MotionSensorDriver  *driver;
    MotionSensorHandler *handler;
  
  int                  lastMesureDistance;
  int                  beforeMesureDistance;
  
  int                  lastMesureTime;
  bool                 successfulMesureBefore;

  virtual void emitOnDistanceUpdated(int oldDistance, int newDistance);
  
  public:

  MotionSensor(MotionSensorDriver* driver);

  int getDistance() { return (lastMesureDistance); }

  void setHandler(MotionSensorHandler *handler) { this->handler = handler; }
  MotionSensorHandler *getHandler() { return(this->handler); }

  virtual void setup();
  virtual void loop();
};

// May be located in separated module

class MotionSensorHandlerDispatcher : public MotionSensorHandler
{
  public:

  enum
  {
    MAX_SUB_HANDLERS = 5,  
  };

  protected:

  MotionSensorHandler *handlers[MAX_SUB_HANDLERS];
  unsigned int         handlersCount;
  
  public:

  MotionSensorHandlerDispatcher() : handlersCount(0) {}
  
  virtual
  void onDistanceUpdated(DistanceUpdatedEvent *event);

  bool addSubHandler(MotionSensorHandler *handler);
  bool removeSubHandler(MotionSensorHandler *handler);
};

#endif // __MOTION_SENSOR_H__

