#include "Speaker.h"

#define FREQUENCY    (490)  // in Hz

#include <Arduino.h>

Speaker::Speaker(int pin)
{
  this->pin = pin;
}

void Speaker::setup()
{
  pinMode(pin, OUTPUT);
}

void Speaker::set(bool active)
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

void Speaker::setSoundBlink(int period)
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
  
bool Speaker::isActive()
{
  return(activity);
}

void Speaker::loop()
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


