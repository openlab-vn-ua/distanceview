#include  <Arduino.h>
#include "DistanceSensor.h"
#include "DistanceIndicatorScreen.h"

#define TIME_BETWEEN_MESURE_DISTANCE           (150) // documentation says that safe time between measurements is 20ms, but experiment shows that real safe period is ~150ms

DistanceSensor::DistanceSensor(DriverDistanceSensor* driver)
{
  this->driver                        = driver;
  this->lastMesureDistance            = DISTANCE_UNKNOWN;
  this->beforeMesureDistance          = DISTANCE_UNKNOWN;
  this->successfulMesureBefore        = false;
  this->handler                       = NULL;
}

void DistanceSensor::setup()
{
  driver->setup();
  lastMesureTime = millis();
}

void DistanceSensor::emitOnDistanceUpdated(int oldDistance, int newDistance)
{
  if (handler != NULL)
  { 
    DistanceSensorHandler::DistanceUpdatedEvent currentEvent;
    
    currentEvent.oldDistance = oldDistance;
    currentEvent.newDistance = newDistance;
    currentEvent.source      = this;
    
    handler->onDistanceUpdated(&currentEvent);
  }
}

void DistanceSensor::loop()
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
