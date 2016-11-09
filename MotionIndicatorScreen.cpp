#include "MotionIndicatorScreen.h"
#include "MotionSensor.h"

#define TIME_BETWEEN_UPDATE      (1000)
#define TIME_BETWEEN_GET_DISTANCE (10)
#define INFINITY                 (10000)


#define SET_POINT                (10)
#define THREE_SIGNIFICANT_DIGITS (100)
#define FOUR_SIGNIFICANT_DIGITS  (1000)
#define OUTPUT__LENGTH           (6)

MotionIndicatorScreen::MotionIndicatorScreen()
 {
   motionSensorsCount = 0;
   lastUpdateTs       = 0;
   lastGettingTs      = 0;
   this->screen       = NULL;
 }

void MotionIndicatorScreen::printDistance(int distance)
{
  if (distance == MotionSensor::DISTANCE_UNKNOWN)
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

void MotionIndicatorScreen::addMotionSensorToListen(MotionSensor *handler, unsigned int pos)
{
  if (motionSensorsCount < pos)
  {
    addMotionSensorToListen(handler);
  }
  else
  {
    bool addedBefore = false;
    for(unsigned int i = 0; i < motionSensorsCount; i++)
    {
      if (motionSensors[i] == handler)
      {
        addedBefore = true;
      }
    }
    if (!addedBefore)
    {
      for (int i = motionSensorsCount; i > pos; i--)
      {
        motionSensors[i] = motionSensors[i - 1];
      }
      motionSensorsCount++;
      motionSensors[pos] = handler;
    }
  }
}

void MotionIndicatorScreen::addMotionSensorToListen(MotionSensor *handler)
{
  if (motionSensorsCount < MotionIndicatorScreen::MAX_COUNT_MOTION_SENSORS)
  {
    addMotionSensorToListen(handler, motionSensorsCount);
  }
}

void MotionIndicatorScreen::removeMotionSensorToListen(MotionSensor *handler)
{
  for (unsigned int i = 0; i < motionSensorsCount; i++)
  {
    if (motionSensors[i] == handler)
    {
      motionSensorsCount--;
      
      for (int ii = i; ii < motionSensorsCount; i++)
      {
        motionSensors[ii] = motionSensors[ii + 1]; 
      } 
    }
  }
}

MotionSensor* MotionIndicatorScreen::getMotionSensorsItem(unsigned int pos)
{
  if (pos < motionSensorsCount)
  {
    return motionSensors[pos];
  }
}

void MotionIndicatorScreen::setup()
{
  screen->begin(16, 2);
  screen->backlight(); 
}

void MotionIndicatorScreen::printSensorName(int sensorIndex)
{
  if (sensorIndex == 0)
  {
    screen->print("Left");
  }
  else if (sensorIndex == 1)
  {
    screen->print("Right");
  }
  else
  {
    screen->print("Sens.N");    
    screen->print(sensorIndex+1);
  }
}

void MotionIndicatorScreen::doAction()
{
  screen->setCursor(0, 0);  
  screen->print("            ");

  minV = INFINITY;
  maxV = 0;
  averageV = 0;
  for (unsigned int i = 0; i < COUNT_GETTING; i++)
  {
    if (minV > V[i])
    {
      minV = V[i]; 
    }
    if (maxV < V[i])
    {
      maxV = V[i]; 
    }
    averageV += V[i];
  }
  screen->setCursor(0, 0);
  screen->print(minV);

  screen->setCursor(6, 0);
  screen->print(maxV);

  screen->setCursor(0, 1);
  screen->print("            ");

  screen->setCursor(3, 1);
  screen->print(averageV / COUNT_GETTING);
  
}

void MotionIndicatorScreen::updateData()
{
  V[counterV] = motionSensors[0]->getDistance();
  counterV++;
  counterV %= COUNT_GETTING;
}

void MotionIndicatorScreen::loop()
{
  unsigned int currentTime = millis();
  
  if (lastUpdateTs <= 0 || currentTime - lastUpdateTs >= TIME_BETWEEN_UPDATE)
  {
    doAction(); 
    lastUpdateTs = millis();
  }
  currentTime = millis();
  if (lastGettingTs <= 0 || currentTime - lastGettingTs >= TIME_BETWEEN_GET_DISTANCE)
  { 
    updateData(); 
    lastGettingTs = millis();
  }
}

