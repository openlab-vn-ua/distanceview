#include "DistanceIndicatorScreen.h"
#include "DistanceSensor.h"

#define TIME_BETWEEN_UPDATE      (1000)

#define SET_POINT                (10)
#define THREE_SIGNIFICANT_DIGITS (100)
#define FOUR_SIGNIFICANT_DIGITS  (1000)
#define OUTPUT__LENGTH           (5)

DistanceIndicatorScreen::DistanceIndicatorScreen()
 {
   distanceSensorsCount = 0;
   lastUpdateTs = 0;
   this->screen = NULL;
 }

void DistanceIndicatorScreen::printDistance(int distance)
{
  if (distance == DistanceSensor::DISTANCE_UNKNOWN)
  {
    screen->print("?    ");
  }
  else
  {
    screen->print(distance / SET_POINT);
    screen->print(".");
    screen->print(distance % SET_POINT);
    
    if(distance < FOUR_SIGNIFICANT_DIGITS)
    {
      screen->print(" ");
    }
    
    if(distance < THREE_SIGNIFICANT_DIGITS)
    {
      screen->print(" ");
    }    
  }
}

void DistanceIndicatorScreen::addDistanceSensorToListen(DistanceSensor *handler, unsigned int pos)
{
  if (distanceSensorsCount < pos)
  {
    addDistanceSensorToListen(handler);
  }
  else
  {
    bool addedBefore = false;
    for(unsigned int i = 0; i < distanceSensorsCount; i++)
    {
      if (distanceSensors[i] == handler)
      {
        addedBefore = true;
      }
    }
    if (!addedBefore)
    {
      for (int i = distanceSensorsCount; i > pos; i--)
      {
        distanceSensors[i] = distanceSensors[i - 1];
      }
      distanceSensorsCount++;
      distanceSensors[pos] = handler;
    }
  }
}

void DistanceIndicatorScreen::addDistanceSensorToListen(DistanceSensor *handler)
{
  if (distanceSensorsCount < DistanceIndicatorScreen::MAX_COUNT_MOTION_SENSORS)
  {
    addDistanceSensorToListen(handler, distanceSensorsCount);
  }
}

void DistanceIndicatorScreen::removeDistanceSensorToListen(DistanceSensor *handler)
{
  for (unsigned int i = 0; i < distanceSensorsCount; i++)
  {
    if (distanceSensors[i] == handler)
    {
      distanceSensorsCount--;
      
      for (int ii = i; ii < distanceSensorsCount; i++)
      {
        distanceSensors[ii] = distanceSensors[ii + 1]; 
      } 
    }
  }
}

DistanceSensor* DistanceIndicatorScreen::getDistanceSensorsItem(unsigned int pos)
{
  if (pos < distanceSensorsCount)
  {
    return distanceSensors[pos];
  }
}

void DistanceIndicatorScreen::setup()
{
  screen->begin(16, 2);
  screen->backlight(); 
}

void DistanceIndicatorScreen::printSensorName(int sensorIndex)
{
  screen->print("S.N");    
  screen->print(sensorIndex+1);
}

void DistanceIndicatorScreen::doAction()
{
  screen->setCursor(0, 0);
  screen->print("                ");
  for (unsigned int i = 0; i < distanceSensorsCount; i++)
  {
    screen->setCursor(i * OUTPUT__LENGTH, 0);
    
    this->printSensorName(i);
  }
  screen->setCursor(0, 1);
  screen->print("                ");
  for (unsigned int i = 0; i < distanceSensorsCount; i++)
  {
    screen->setCursor(i * OUTPUT__LENGTH, 1);    
    int distance = distanceSensors[i]->getDistance();
    this->printDistance(distance);
  }  
}

void DistanceIndicatorScreen::loop()
{
  unsigned int currentTime = millis();
  
  if (lastUpdateTs <= 0 || currentTime - lastUpdateTs >= TIME_BETWEEN_UPDATE)
  {
    doAction(); 
    lastUpdateTs = millis();
  }
}

