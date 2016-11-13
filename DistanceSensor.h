#ifndef __MOTION_SENSOR_H__
#define __MOTION_SENSOR_H__

#include "DriverDistanceSensor.h"
#include "Process.h"

// Distance Sensor ans Distance Sensor Handler
// ---------------------------

class DistanceSensor;

class DistanceSensorHandler
{
  public:

   class Event
   {
     public:

      DistanceSensor  *source;
   };

   class DistanceUpdatedEvent : public Event
   {
     public:
    
      int            oldDistance; /// DEPRECATED
      int            newDistance;
   };

   virtual void      onDistanceUpdated(DistanceUpdatedEvent *event) = 0;
};

class DistanceSensor : public Process
{
  public:

   enum
   {
     DISTANCE_UNKNOWN = DriverDistanceSensor::DISTANCE_UNKNOWN,
   };

  protected:
  
   DriverDistanceSensor  *driver;
   DistanceSensorHandler *handler;
  
   int                  lastMesureDistance;
   int                  beforeMesureDistance;
  
   int                  lastMesureTime;
   bool                 successfulMesureBefore;

   virtual void         emitOnDistanceUpdated(int oldDistance, int newDistance);
  
  public:

   DistanceSensor(DriverDistanceSensor* driver);

   int                  getDistance() { return (lastMesureDistance); }

   void                 setHandler(DistanceSensorHandler *handler) { this->handler = handler; }
   
   DistanceSensorHandler *getHandler() { return(this->handler); }

  virtual void          setup();
  virtual void          loop();
};

#endif // __MOTION_SENSOR_H__

