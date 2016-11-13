#ifndef __CONTROLLER_SPEAKER_H__
#define __CONTROLLER_SPEAKER_H__

#include "Process.h"

// Controller Speaker
// ---------------------------

class ControllerSpeaker : public Process
{
  protected:

   int          pin;
   bool         soundBlinking;
   bool         activity;
   bool         statusSound;
   int          period;
   unsigned int switchTimeStamp;

  public:

   ControllerSpeaker(int pin);

   void         set(bool active);
   void         setSoundBlink(int period);
   bool         isActive();

   virtual void setup();
   virtual void loop();
};

#endif // __CONTROLLER_SPEAKER_H__

