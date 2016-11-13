#include "ControllerLed.h"

#include <Arduino.h>

ControllerLed::ControllerLed(int pin)
{
  this->pin = pin;
}

void ControllerLed::setup()
{
  pinMode(pin, OUTPUT);
}

void ControllerLed::set(bool active)
{
  blinking = false;
  if (active)
  {  
    digitalWrite(pin, HIGH);
    activity = true;
  }
  else
  {  
    digitalWrite(pin, LOW);
    activity = false;
  }
}

void ControllerLed::setBlink(int period)
{
  if (!blinking)
  {
    blinking        = true;
    activity        = true;
    switchTimestamp = millis();
  }
  this->period      = period;
}
  
bool ControllerLed::isActive()
{
  return(activity);
}

void ControllerLed::loop()
{
  if (blinking == true)
  {
    unsigned int now        = millis();
    unsigned int passedTime = now - switchTimestamp;
    
    if (passedTime >= period)
    {
       if (digitalRead(pin) == HIGH)
       {
          digitalWrite(pin, LOW);
       }
       else
       {
          digitalWrite(pin, HIGH);
       }  
       
       switchTimestamp = now;
    }
  }
}


