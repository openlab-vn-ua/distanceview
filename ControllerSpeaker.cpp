#include "ControllerSpeaker.h"

#define FREQUENCY    (490)  // in Hz

#include <Arduino.h>

ControllerSpeaker::ControllerSpeaker(int pin)
{
  this->pin = pin;
}

void ControllerSpeaker::setup()
{
  pinMode(pin, OUTPUT);
}

void ControllerSpeaker::set(bool active)
{
  soundBlinking = false;
  if (active)
  {  
    tone(pin, FREQUENCY);
    statusSound = true;
    activity    = true;
  }
  else
  {  
    noTone(pin);
    statusSound = false;
    activity    = false;
  }
}

void ControllerSpeaker::setSoundBlink(int period)
{
  if (!soundBlinking)
  {
    soundBlinking   = true;
    activity        = true;
    statusSound     = true;
    switchTimeStamp = millis();
  }
  
  this->period      = period;
}
  
bool ControllerSpeaker::isActive()
{
  return(activity);
}

void ControllerSpeaker::loop()
{
  if (soundBlinking == true)
  {
    unsigned int now        = millis();
    unsigned int passedTime = now - switchTimeStamp;
    
    if (passedTime >= period)
    {
       if (statusSound)
       {
          noTone(pin);
          statusSound  = false;
       }
       else
       {
          tone(pin, FREQUENCY);
          statusSound  = true;
       }
       
       switchTimeStamp = now;
    }
  }
}


