#include <Arduino.h>

#include "Led.h"
#include "MotionIndicatorLedAndSpeaker.h"
#include "MotionSensor.h"
#include "Process.h"
#include "Speaker.h"
#include "MotionIndicatorScreen.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define SPEAKER_PIN                  (9)

#define LEFT_LED_PIN                 (10)
#define LEFT_TRIG_PIN                (11)
#define LEFT_ECHO_PIN                (12)

#define RIGHT_LED_PIN                (4)
#define RIGHT_TRIG_PIN               (5)
#define RIGHT_ECHO_PIN               (6)

#define MAX_DISTANCE                 (3000)    // in mm

#define MOTION_SENSOR_COUNT          (2)
#define LED_COUNT                    (2)


enum
{
  LEFT = 0, 
  RIGHT = 1,
};

Led                            leds[LED_COUNT] ={
                                        Led(LEFT_LED_PIN),
                                        Led(RIGHT_LED_PIN),
                                       };

Speaker                        speaker(SPEAKER_PIN);

MotionIndicatorLed             motionIndicatorLeds[LED_COUNT];

MotionIndicatorSpeaker         motionIndicatorSpeaker;

MotionSensor                   motionSensors[MOTION_SENSOR_COUNT] = {
                                                  MotionSensor(LEFT_TRIG_PIN,  LEFT_ECHO_PIN), 
                                                  MotionSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN)
                                                 };

MotionSensorHandlerDispatcher  motionSensorHandlerDispatchers[MOTION_SENSOR_COUNT]; 

ProcessDispatcher              processDispatcher;

LiquidCrystal_I2C newScreen(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

MotionIndicatorScreen screen;

void setup()
{ 
  Serial.begin (9600);
   
  screen.attachScreen(&newScreen);
  
  processDispatcher.addSubProcess(&motionSensors[LEFT]);
  processDispatcher.addSubProcess(&motionSensors[RIGHT]);
  processDispatcher.addSubProcess(&leds[LEFT]);
  processDispatcher.addSubProcess(&leds[RIGHT]);
  processDispatcher.addSubProcess(&speaker);
  processDispatcher.addSubProcess(&screen);
  
  processDispatcher.setup();
  
  motionIndicatorLeds[LEFT].attachLed(&leds[LEFT]);
  motionIndicatorLeds[RIGHT].attachLed(&leds[RIGHT]);
  motionIndicatorSpeaker.attachSpeaker(&speaker);
  
  motionSensors[LEFT].setHandler(&motionSensorHandlerDispatchers[LEFT]);
  motionSensors[RIGHT].setHandler(&motionSensorHandlerDispatchers[RIGHT]);
  
  motionSensorHandlerDispatchers[LEFT].addSubHandler(&motionIndicatorLeds[LEFT]);
  motionSensorHandlerDispatchers[LEFT].addSubHandler(&motionIndicatorSpeaker);
  motionIndicatorSpeaker.startListenMotionSensor(&motionSensors[LEFT]);

  motionSensorHandlerDispatchers[RIGHT].addSubHandler(&motionIndicatorLeds[RIGHT]);
  motionSensorHandlerDispatchers[RIGHT].addSubHandler(&motionIndicatorSpeaker);
  motionIndicatorSpeaker.startListenMotionSensor(&motionSensors[RIGHT]);

  screen.addMotionSensorToListen(&motionSensors[LEFT], LEFT);
  screen.addMotionSensorToListen(&(motionSensors[RIGHT]), RIGHT);
}

void loop()
{  
  processDispatcher.loop();
//  motionSensors[LEFT].loop();
}

