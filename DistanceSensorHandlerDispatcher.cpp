#include  <Arduino.h>
#include "DistanceSensorHandlerDispatcher.h"
#include "DistanceIndicatorScreen.h"

bool DistanceSensorHandlerDispatcher::addSubHandler(DistanceSensorHandler *handler)
{
  if (handler == NULL || handlersCount == MAX_SUB_HANDLERS)
  {
    return false;
  }

  for (unsigned int i = 0; i < handlersCount; i++)
  {
    if (handlers[i] == handler)
    {
      return false;
    }
  }

  handlers[handlersCount++] = handler;
  return true;
}

bool DistanceSensorHandlerDispatcher::removeSubHandler(DistanceSensorHandler *handler)
{
  if (handler == NULL || handlersCount == 0)
  {
    return false;
  }

  for (unsigned int i = 0; i < handlersCount; i++)
  {
    if (handlers[i] == handler)
    {
      for (unsigned int ii = i + 1; ii < handlersCount; ii++)
      {
        handlers[ii - 1] = handlers[ii]; 
      }
 
      handlersCount--;
      return true;
    }
  }
 
  return false;
}

void DistanceSensorHandlerDispatcher::onDistanceUpdated(DistanceUpdatedEvent *event)
{
  DistanceSensorHandler *handlers2call[MAX_SUB_HANDLERS];

  memcpy(&handlers2call, &this->handlers, sizeof(handlers2call[0]) * handlersCount);
  
  for (unsigned int i = 0; i < handlersCount; i++)
  {
    handlers2call[i]->onDistanceUpdated(event);
  }
}

