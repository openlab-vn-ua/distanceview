#include <Arduino.h>
#include "Process.h"

bool ProcessDispatcher::addSubProcess(Process *process)
{
  if (process == NULL || handlersCount >= MAX_SUB_PROCESSES)
  {
    return false;
  }
  
  for (unsigned int i = 0; i < handlersCount; i++)
  {
    if (handlers[i] == process)
    {
      return true;
    }
  }

  handlers[handlersCount++] = process;
  return true;
}

bool ProcessDispatcher::removeSubProcess(Process *process)
{
  if (process == NULL || handlersCount <= 0)
  {
    return false;
  }
  
  for (unsigned int i = 0; i < handlersCount; i++)
  {
    if (handlers[i] == process)
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


void ProcessDispatcher::setup()
{
  Process *handlers2call[MAX_SUB_PROCESSES];
  
  memcpy(&handlers2call, &this->handlers, sizeof(handlers2call[0]) * handlersCount);

  for (unsigned int i = 0; i < handlersCount; i++)
  {
    handlers2call[i]->setup();
  }
}


void ProcessDispatcher::loop()
{
  Process *handlers2call[MAX_SUB_PROCESSES];
  
  memcpy(&handlers2call, &this->handlers, sizeof(handlers2call[0]) * handlersCount);

  for (unsigned int i = 0; i < handlersCount; i++)
  {
    handlers2call[i]->loop();
  }
}


