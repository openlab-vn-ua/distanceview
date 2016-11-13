#include <Arduino.h>
#include "DistanceIndicatorLed.h"

#define BLINKING_DISTANCE              (300)    // in mm
#define ACTIVE_DISTANCE                (50)     // in mm
#define MULTIPLIER                     (0.5)

DistanceIndicatorLed::DistanceIndicatorLed(ControllerLed *ledToAttach)
{
  currentLed = ledToAttach;
}

void DistanceIndicatorLed::setup()
{
}

void DistanceIndicatorLed::changeIllumination(int newDistance)
{
  if (currentLed == NULL)
  {
    return;
  }
  
  if (newDistance > BLINKING_DISTANCE || newDistance == DistanceSensor::DISTANCE_UNKNOWN)
  {
    currentLed->set(false);
  }
  else if (newDistance > ACTIVE_DISTANCE)
  {
    currentLed->setBlink(newDistance * MULTIPLIER);
  }
  else
  {
    currentLed->set(true);
  }
}

void DistanceIndicatorLed::onDistanceUpdated(DistanceUpdatedEvent *event)
{
  changeIllumination(event->newDistance);
}

void DistanceIndicatorLed::attachLed(ControllerLed *ledToAttach)
{
  currentLed = ledToAttach;
}

void DistanceIndicatorLed::detachLed()
{
  currentLed = NULL;
}

void DistanceIndicatorLed::loop()
{
  if (currentLed == NULL)
  {
    return;
  }
}
