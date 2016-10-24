#ifndef __MOTION_INDICATOR_SCREEN_H__
#define __MOTION_INDICATOR_SCREEN_H__

#include "MotionSensor.h" 
#include "Process.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class MotionIndicatorScreen : public Process
{
  protected:
 
  enum
  {
    MAX_COUNT_MOTION_SENSORS = 3,
  };

  LiquidCrystal_I2C *screen;
  MotionSensor      *motionSensors[MAX_COUNT_MOTION_SENSORS];
  unsigned int       motionSensorsCount;
  unsigned int       lastUpdateTs;
  
  void printDistance(int distance);
  void printSensorName(int sensorIndex);
  
  void doAction();
  
  public:

  void addMotionSensorToListen(MotionSensor *handler, unsigned int pos);
  void addMotionSensorToListen(MotionSensor *handler);
  void removeMotionSensorToListen(MotionSensor *handler);
  
  unsigned int   getMotionSensorsCount() { return(motionSensorsCount); }
  MotionSensor  *getMotionSensorsItem(unsigned int pos);
  
  MotionIndicatorScreen();

  void attachScreen(LiquidCrystal_I2C *screenToAttach) {screen = screenToAttach;}
  void detachScreen(){screen = NULL;}
    
  virtual void setup();
  virtual void loop();
};

#endif // __MOTION_INDICATOR_SCREEN_H__