#ifndef __SPEAKER_H__
#define __SPEAKER_H__

#include "Process.h"

// Speaker driver
// ---------------------------

class Speaker : public Process
{
  protected:

  int  pin;
  bool soundBlinking;
  bool activity;
  bool statusSound;
  int  period;
  unsigned int switchTimeStamp;

  public:

  Speaker(int pin);

  void set(bool active);
  void setSoundBlink(int period);
  bool isActive();

  virtual void setup();
  virtual void loop();
};

#endif // __SPEAKER_H__

