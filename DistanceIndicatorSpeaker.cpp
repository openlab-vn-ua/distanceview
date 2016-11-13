#include <Arduino.h>
#include "DistanceIndicatorSpeaker.h"

#define BLINKING_DISTANCE              (300)    // in mm
#define ACTIVE_DISTANCE                (50)     // in mm
#define MULTIPLIER                     (0.5)

DistanceIndicatorSpeaker::DistanceIndicatorSpeaker(ControllerSpeaker *speakerToAttach)
{
  currentSpeaker = speakerToAttach;
 
  for(unsigned int i = 0; i < MAX_COUNT_MOTION_SENSORS; i++)
  {
      distance[i] =  DistanceSensor::DISTANCE_UNKNOWN;
  }  
 
  
  distanceSensorsToListenCount = 0;
}

void DistanceIndicatorSpeaker::setup()
{
}
  
void DistanceIndicatorSpeaker::changeSound(int newDistance)
{ 
  if (currentSpeaker == NULL)
  {
    return;
  }

  if (newDistance > BLINKING_DISTANCE || newDistance == DistanceSensor::DISTANCE_UNKNOWN)
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

void DistanceIndicatorSpeaker::onDistanceUpdated(DistanceUpdatedEvent *event)
{  
  bool distanceSensorDistanceFound = false;
  int  i;

  i = 0;
  while ((i < distanceSensorsToListenCount) && (!distanceSensorDistanceFound))
  {
    if (event->source == distanceSensorsToListen[i])
    {
      distance[i] = event->newDistance;
      distanceSensorDistanceFound = true;
    }
    else
    {
      i++;
    }
  }

  // find average exsiting distance from data, wich we have. If it doesn't exist, than we take DistanceSensor::DISTANCE_UNKNOWN
  int averageExistingDistance        = DistanceSensor::DISTANCE_UNKNOWN;
  unsigned int countExistingDistance = 0;

  for (int i = 0; i < distanceSensorsToListenCount; i++)
  {
    int currentDistanceSensorDistance = distance[i];
    if (currentDistanceSensorDistance != DistanceSensor::DISTANCE_UNKNOWN)
    {
      countExistingDistance++;
      if (averageExistingDistance == DistanceSensor::DISTANCE_UNKNOWN)
      {
        averageExistingDistance = currentDistanceSensorDistance;
      }
      else
      {
        averageExistingDistance += currentDistanceSensorDistance;
      }
    }
  }

  if (countExistingDistance <= 0)
  {
    changeSound(DistanceSensor::DISTANCE_UNKNOWN);
  }
  else
  {
    changeSound(averageExistingDistance / countExistingDistance);
  }
}

bool DistanceIndicatorSpeaker::startListenDistanceSensor(DistanceSensor *distanceSensorToListen)
{
  if (distanceSensorToListen == NULL || distanceSensorsToListenCount >= MAX_COUNT_MOTION_SENSORS)
  {
    return false;
  }

  for (unsigned int i = 0; i < distanceSensorsToListenCount; i++)
  {
    if (distanceSensorsToListen[i] == distanceSensorToListen)
    {
      return false; // Already here
    }
  }

  distanceSensorsToListen[distanceSensorsToListenCount] = distanceSensorToListen;
  distance[distanceSensorsToListenCount] = DistanceSensor::DISTANCE_UNKNOWN;
  distanceSensorsToListenCount++;

  return true;
}

bool DistanceIndicatorSpeaker::stopListenDistanceSensor(DistanceSensor *distanceSensorToListen)
{
  if (distanceSensorToListen == NULL || distanceSensorsToListenCount <= 0)
  {
    return false;
  }

  for (unsigned int i = 0; i < distanceSensorsToListenCount; i++)
  {
    if (distanceSensorsToListen[i] == distanceSensorToListen)
    {
      for (unsigned int ii = i + 1; ii < distanceSensorsToListenCount; ii++)
      {
        distanceSensorsToListen[ii - 1] = distanceSensorsToListen[ii]; 
        distance[ii - 1] = distance[ii]; 
      }
 
      distanceSensorsToListenCount--;
      return true;
    }
  }
 
  return false;
}


void DistanceIndicatorSpeaker::attachSpeaker(ControllerSpeaker *speakerToAttach)
{
  currentSpeaker = speakerToAttach;
}

void DistanceIndicatorSpeaker::detachSpeaker()
{
  currentSpeaker = NULL;
}

void DistanceIndicatorSpeaker::loop()
{
  if (currentSpeaker == NULL)
  {
    return;
  }

  //currentSpeaker->loop();
}

