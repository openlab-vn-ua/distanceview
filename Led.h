#ifndef __LED_H__
#define __LED_H__

#include "Process.h"

// LED driver
// ---------------------------

class Led : public Process
{
  protected:

  int  pin;
  bool blinking;
  bool activity;
  int  period;
  unsigned int switchTimestamp;

  public:

  Led(int pin);

  void set(bool active);
  void setBlink(int period);
  bool isActive();

  virtual void setup();
  virtual void loop();
  virtual void onRemoveHandler(Process *process){};
};

#endif // __LED_H__

