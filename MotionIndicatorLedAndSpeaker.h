#ifndef __MOTION_INDICATOR_LED_AND_SPEAKER_H__
#define __MOTION_INDICATOR_LED_AND_SPEAKER_H__

#include "LED.h"
#include "MotionSensor.h"
#include "Speaker.h"

// MOTION_INDICATOR_LED_AND_SPEAKER 
// ---------------------------

class MotionIndicatorLed : public MotionSensorHandler, public Process
{
  protected:

  Led                 *currentLed;
  
  void                 changeIllumination(int newDistance);

  virtual 
  void                 onDistanceUpdated(DistanceUpdatedEvent *event);

  public:

  MotionIndicatorLed(Led *ledToAttach = NULL);

  void attachLed(Led *newLed);
  void detachLed();

  virtual void setup();
  virtual void loop();
};

class MotionIndicatorSpeaker : public MotionSensorHandler, public Process
{
  protected:

  enum
  {
    MAX_COUNT_MOTION_SENSORS = 2,
  };
  
  int                  distance[MAX_COUNT_MOTION_SENSORS];
  MotionSensor        *motionSensorsToListen[MAX_COUNT_MOTION_SENSORS];
  int                  motionSensorsToListenCount;
  
  Speaker             *currentSpeaker;
  
  void                 changeSound(int newDistance);

  virtual 
  void                 onDistanceUpdated(DistanceUpdatedEvent *event);

  public:

  MotionIndicatorSpeaker(Speaker *speakerToAttach = NULL);

  // Call startListenMotionSensor to enable data collection from it
  // Note: You have to explicitly set this class as MotionSensorHandler as well
  bool startListenMotionSensor(MotionSensor *owner);
  bool stopListenMotionSensor(MotionSensor *owner);

  void attachSpeaker(Speaker *speakerToAttach);
  void detachSpeaker();

  virtual void setup();
  virtual void loop();
};

#endif // __MOTION_INDICATOR_LED_AND_SPEAKER_H__

