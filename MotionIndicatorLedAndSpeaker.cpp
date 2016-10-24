#include <Arduino.h>
#include "MotionIndicatorLedAndSpeaker.h"

#define BLINKING_DISTANCE              (300)    // in mm
#define ACTIVE_DISTANCE                (50)     // in mm
#define MULTIPLIER                     (0.5)

MotionIndicatorLed::MotionIndicatorLed(Led *ledToAttach)
{
  currentLed = ledToAttach;
}

void MotionIndicatorLed::setup()
{
}

void MotionIndicatorLed::changeIllumination(int newDistance)
{
  if (currentLed == NULL)
  {
    return;
  }
  
  if (newDistance > BLINKING_DISTANCE || newDistance == MotionSensor::DISTANCE_UNKNOWN)
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

void MotionIndicatorLed::onDistanceUpdated(DistanceUpdatedEvent *event)
{
  changeIllumination(event->newDistance);
}

void MotionIndicatorLed::attachLed(Led *ledToAttach)
{
  currentLed = ledToAttach;
}

void MotionIndicatorLed::detachLed()
{
  currentLed = NULL;
}

void MotionIndicatorLed::loop()
{
  if (currentLed == NULL)
  {
    return;
  }
    //currentLed->loop();
}



MotionIndicatorSpeaker::MotionIndicatorSpeaker(Speaker *speakerToAttach)
{
  currentSpeaker = speakerToAttach;
/*  
  for(unsigned int i = 0; i < MAX_COUNT_MOTION_SENSORS; i++)
  {
      distance[i] =  MotionSensor::DISTANCE_UNKNOWN;
  }  
 */
  
  motionSensorsToListenCount = 0;
}

void MotionIndicatorSpeaker::setup()
{
}
  
void MotionIndicatorSpeaker::changeSound(int newDistance)
{ 
  if (currentSpeaker == NULL)
  {
    return;
  }

  if (newDistance > BLINKING_DISTANCE || newDistance == MotionSensor::DISTANCE_UNKNOWN)
  {
    currentSpeaker->set(false);
  }
  else if (newDistance > ACTIVE_DISTANCE)
  {
    currentSpeaker->setSoundBlink(newDistance * MULTIPLIER);
  }
  else
  {
    currentSpeaker->set(true);
  }
}

void MotionIndicatorSpeaker::onDistanceUpdated(DistanceUpdatedEvent *event)
{  
  bool motionSensorDistanceFound = false;
  int  i;

  i = 0;
  while ((i < motionSensorsToListenCount) && (!motionSensorDistanceFound))
  {
    if (event->source == motionSensorsToListen[i])
    {
      distance[i] = event->newDistance;
      motionSensorDistanceFound = true;
    }
    else
    {
      i++;
    }
  }

  // find average exsiting distance from data, wich we have. If it doesn't exist, than we take MotionSensor::DISTANCE_UNKNOWN
  int averageExistingDistance        = MotionSensor::DISTANCE_UNKNOWN;
  unsigned int countExistingDistance = 0;

  for (int i = 0; i < motionSensorsToListenCount; i++)
  {
    int currentMotionSensorDistance = distance[i];
    if (currentMotionSensorDistance != MotionSensor::DISTANCE_UNKNOWN)
    {
      countExistingDistance++;
      if (averageExistingDistance == MotionSensor::DISTANCE_UNKNOWN)
      {
        averageExistingDistance = currentMotionSensorDistance;
      }
      else
      {
        averageExistingDistance += currentMotionSensorDistance;
      }
    }
  }

  if (countExistingDistance <= 0)
  {
    changeSound(MotionSensor::DISTANCE_UNKNOWN);
  }
  else
  {
    changeSound(averageExistingDistance / countExistingDistance);
  }
}

bool MotionIndicatorSpeaker::startListenMotionSensor(MotionSensor *motionSensorToListen)
{
  if (motionSensorToListen == NULL || motionSensorsToListenCount >= MAX_COUNT_MOTION_SENSORS)
  {
    return false;
  }

  for (unsigned int i = 0; i < motionSensorsToListenCount; i++)
  {
    if (motionSensorsToListen[i] == motionSensorToListen)
    {
      return false; // Already here
    }
  }

  motionSensorsToListen[motionSensorsToListenCount] = motionSensorToListen;
  distance[motionSensorsToListenCount] = MotionSensor::DISTANCE_UNKNOWN;
  motionSensorsToListenCount++;

  return true;
}

bool MotionIndicatorSpeaker::stopListenMotionSensor(MotionSensor *motionSensorToListen)
{
  if (motionSensorToListen == NULL || motionSensorsToListenCount <= 0)
  {
    return false;
  }

  for (unsigned int i = 0; i < motionSensorsToListenCount; i++)
  {
    if (motionSensorsToListen[i] == motionSensorToListen)
    {
      for (unsigned int ii = i + 1; ii < motionSensorsToListenCount; ii++)
      {
        motionSensorsToListen[ii - 1] = motionSensorsToListen[ii]; 
        distance[ii - 1] = distance[ii]; 
      }
 
      motionSensorsToListenCount--;
      return true;
    }
  }
 
  return false;
}


void MotionIndicatorSpeaker::attachSpeaker(Speaker *speakerToAttach)
{
  currentSpeaker = speakerToAttach;
}

void MotionIndicatorSpeaker::detachSpeaker()
{
  currentSpeaker = NULL;
}

void MotionIndicatorSpeaker::loop()
{
  if (currentSpeaker == NULL)
  {
    return;
  }

  //currentSpeaker->loop();
}

