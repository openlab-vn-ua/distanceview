#ifndef __MOTION_INDICATOR_LED_H__
#define __MOTION_INDICATOR_LED_H__

#include "ControllerLed.h"
#include "DistanceSensor.h"

// Distance Indicator Led
// ---------------------------

class DistanceIndicatorLed : public DistanceSensorHandler, public Process
{
  protected:

   ControllerLed *currentLed;
  
   void           changeIllumination(int newDistance);

   virtual void   onDistanceUpdated(DistanceUpdatedEvent *event);

  public:

   DistanceIndicatorLed(ControllerLed *ledToAttach = NULL);

   void           attachLed(ControllerLed *newLed);
   void           detachLed();

   virtual void   setup();
   virtual void   loop();
};

#endif // __MOTION_INDICATOR_LED_H__

