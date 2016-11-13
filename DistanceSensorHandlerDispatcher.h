#ifndef __MOTION_SENSOR_HANDLER_DISPATCHER_H__
#define __MOTION_SENSOR_HANDLER_DISPATCHER_H__

#include "DriverDistanceSensor.h"
#include "DistanceSensor.h"
#include "Process.h"

// Distance Sensor Handler Dispatcher
// ---------------------------

class DistanceSensorHandlerDispatcher : public DistanceSensorHandler
{
  public:

   enum
   {
     MAX_SUB_HANDLERS = 5,  
   };

  protected:

   DistanceSensorHandler *handlers[MAX_SUB_HANDLERS];
   unsigned int         handlersCount;
  
  public:

   DistanceSensorHandlerDispatcher() : handlersCount(0) {}
  
  virtual void          onDistanceUpdated(DistanceUpdatedEvent *event);

  bool                  addSubHandler(DistanceSensorHandler *handler);
  bool                  removeSubHandler(DistanceSensorHandler *handler);
};

#endif // __MOTION_SENSOR_H__

