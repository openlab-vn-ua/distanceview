#ifndef __PROCESS_H__
#define __PROCESS_H__

class Process
{
  public:
  
   virtual void setup() = 0;
   virtual void loop()  = 0;
};

class ProcessDispatcher : public Process
{
  public:

   enum
   {
     MAX_SUB_PROCESSES = 10,
   };

  protected:

   Process         *handlers[MAX_SUB_PROCESSES];
   unsigned int     handlersCount;

  public:

   ProcessDispatcher() : handlersCount(0) {}
  
   bool             addSubProcess(Process *process);
   bool             removeSubProcess(Process *process);
  
   virtual void     setup();
   virtual void     loop();
};

/*

class PeriodicActionProcess : public Process
{
  protected:

  unsigned int actionPeriod;
  bool         actionOnNextLoop;
  unsigned int actionTimestamp;
  
  public:

  PeriodicActionProcess (unsigned int actionPeriod, bool runActionOnFirstLoop = true)
  {
    this->actionPeriod     = doActionPeriod;
    this->actionOnNextLoop = runActionOnFirstLoop;
    this->actionTimestamp  = 0;
  }

  // actionPeriod period top call action (in ms)
  // if action period is 0, action would not be called on timer
  // if runActionOnNextLoop is true action would be force called on next loop
  // Note: if  actionPeriod=0 and runActionOnNextLoop=true action would be called once on next loop
  
  void setActionPeriod(unsigned int actionPeriod, bool runActionOnNextLoop = true)

  virtual void setup()
  {
    this->actionTimestamp
  }

  virtual void loop();

  // override me with usefull action
  virtual void doAction (void) = 0;
};

*/

#endif // __PROCESS_H__
