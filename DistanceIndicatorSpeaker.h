#ifndef __MOTION_INDICATOR_SPEAKER_H__
#define __MOTION_INDICATOR_SPEAKER_H__

#include "DistanceSensor.h"
#include "ControllerSpeaker.h"

// MOTION_INDICATOR_SPEAKER
// ---------------------------

class DistanceIndicatorSpeaker : public DistanceSensorHandler, public Process
{
  protected:

   enum
   {
     MAX_COUNT_MOTION_SENSORS = 2,
   };
  
   int                distance[MAX_COUNT_MOTION_SENSORS];
   DistanceSensor      *distanceSensorsToListen[MAX_COUNT_MOTION_SENSORS];
   int                distanceSensorsToListenCount;
  
   ControllerSpeaker *currentSpeaker;
  
   void               changeSound(int newDistance);

   virtual void       onDistanceUpdated(DistanceUpdatedEvent *event);

  public:

   DistanceIndicatorSpeaker(ControllerSpeaker *speakerToAttach = NULL);

   // Call startListenDistanceSensor to enable data collection from it
   // Note: You have to explicitly set this class as DistanceSensorHandler as well
   bool               startListenDistanceSensor(DistanceSensor *owner);
   bool               stopListenDistanceSensor(DistanceSensor *owner);

   void               attachSpeaker(ControllerSpeaker *speakerToAttach);
   void               detachSpeaker();

  virtual void        setup();
  virtual void        loop();
};

#endif // __MOTION_INDICATOR_SPEAKER_H__

