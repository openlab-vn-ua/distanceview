#include  <Arduino.h>
#include "MotionSensor.h"
#include "MotionIndicatorScreen.h"

#define TIME_BETWEEN_MESURE_DISTANCE           (150) // documentation says that safe time between measurements is 20ms, but experiment shows that real safe period is ~150ms

MotionSensor::MotionSensor(MotionSensorDriver* driver)
{
  this->driver                        = driver;
  this->lastMesureDistance            = DISTANCE_UNKNOWN;
  this->beforeMesureDistance          = DISTANCE_UNKNOWN;
  this->successfulMesureBefore        = false;
  this->handler                       = NULL;
}

void MotionSensor::setup()
{
  driver->setup();
  lastMesureTime = millis();
}

void MotionSensor::emitOnDistanceUpdated(int oldDistance, int newDistance)
{
  if (handler != NULL)
  { 
    MotionSensorHandler::DistanceUpdatedEvent currentEvent;
    
    currentEvent.oldDistance = oldDistance;
    currentEvent.newDistance = newDistance;
    currentEvent.source      = this;
    
    handler->onDistanceUpdated(&currentEvent);
  }
}

void MotionSensor::loop()
{
  unsigned int now = millis();
  if (!successfulMesureBefore || (now - lastMesureTime) >= TIME_BETWEEN_MESURE_DISTANCE) 
  { 
    beforeMesureDistance = lastMesureDistance;
    lastMesureDistance   = driver->mesureDistance();
    Serial.println(lastMesureDistance);
    emitOnDistanceUpdated(beforeMesureDistance, lastMesureDistance);
  
    if (lastMesureDistance != DISTANCE_UNKNOWN)
    {
      lastMesureTime = millis();
      successfulMesureBefore = true;
    }
    else
    {
      successfulMesureBefore = false;
    }
  }
}

bool MotionSensorHandlerDispatcher::addSubHandler(MotionSensorHandler *handler)
{
  if (handler == NULL || handlersCount == MAX_SUB_HANDLERS)
  {
    return false;
  }

  for (unsigned int i = 0; i < handlersCount; i++)
  {
    if (handlers[i] == handler)
    {
      return false;
    }
  }

  handlers[handlersCount++] = handler;
  return true;
}

bool MotionSensorHandlerDispatcher::removeSubHandler(MotionSensorHandler *handler)
{
  if (handler == NULL || handlersCount == 0)
  {
    return false;
  }

  for (unsigned int i = 0; i < handlersCount; i++)
  {
    if (handlers[i] == handler)
    {
      for (unsigned int ii = i + 1; ii < handlersCount; ii++)
      {
        handlers[ii - 1] = handlers[ii]; 
      }
 
      handlersCount--;
      return true;
    }
  }
 
  return false;
}

void MotionSensorHandlerDispatcher::onDistanceUpdated(DistanceUpdatedEvent *event)
{
  MotionSensorHandler *handlers2call[MAX_SUB_HANDLERS];

  memcpy(&handlers2call, &this->handlers, sizeof(handlers2call[0]) * handlersCount);
  
  for (unsigned int i = 0; i < handlersCount; i++)
  {
    handlers2call[i]->onDistanceUpdated(event);
  }
}

