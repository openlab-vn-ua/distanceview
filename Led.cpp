#include "Led.h"

#include <Arduino.h>

Led::Led(int pin)
{
  this->pin = pin;
}

void Led::setup()
{
  pinMode(pin, OUTPUT);
}

void Led::set(bool active)
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

void Led::setBlink(int period)
{
  if (!blinking)
  {
    blinking        = true;
    activity        = true;
    switchTimestamp = millis();
  }
  this->period      = period;
}
  
bool Led::isActive()
{
  return(activity);
}

void Led::loop()
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


