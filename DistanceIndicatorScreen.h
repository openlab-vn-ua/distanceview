#ifndef __MOTION_INDICATOR_SCREEN_H__
#define __MOTION_INDICATOR_SCREEN_H__

#include "DistanceSensor.h" 
#include "Process.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class DistanceIndicatorScreen : public Process
{
  protected:
 
   enum
   {
     MAX_COUNT_MOTION_SENSORS = 4,
   };

   LiquidCrystal_I2C *screen;
   DistanceSensor      *distanceSensors[MAX_COUNT_MOTION_SENSORS];
   unsigned int       distanceSensorsCount;
   unsigned int       lastUpdateTs;
  
   void               printDistance(int distance);
   void               printSensorName(int sensorIndex);
  
   void               doAction();
  
  public:

   void               addDistanceSensorToListen(DistanceSensor *handler, unsigned int pos);
   void               addDistanceSensorToListen(DistanceSensor *handler);
   void               removeDistanceSensorToListen(DistanceSensor *handler);
  
   unsigned int       getDistanceSensorsCount() { return(distanceSensorsCount); }
   DistanceSensor      *getDistanceSensorsItem(unsigned int pos);
  
   DistanceIndicatorScreen();

   void               attachScreen(LiquidCrystal_I2C *screenToAttach) {screen = screenToAttach;}
   void               detachScreen(){screen = NULL;}
    
   virtual void       setup();
   virtual void       loop();
};

#endif // __MOTION_INDICATOR_SCREEN_H__
