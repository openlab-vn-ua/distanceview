#ifndef __CONTROLLER_LED_H__
#define __CONTROLLER_LED_H__

#include "Process.h"

// Controller Led 
// ---------------------------

class ControllerLed : public Process
{
  protected:

   int          pin;
   bool         blinking;
   bool         activity;
   int          period;
   unsigned int switchTimestamp;

  public:

   ControllerLed(int pin);

   void         set(bool active);
   void         setBlink(int period);
   bool         isActive();

   virtual void setup();
   virtual void loop();
   virtual void onRemoveHandler(Process *process){};
};

#endif // __CONTROLLER_LED_H__

