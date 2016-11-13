#include <Arduino.h>

#include "Process.h"

#include "ControllerLed.h"
#include "ControllerSpeaker.h"

#include "DistanceIndicatorLed.h"
#include "DistanceIndicatorSpeaker.h"
#include "DistanceIndicatorScreen.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "DistanceSensor.h"
#include "DistanceSensorHandlerDispatcher.h"

#include "DriverDistanceSensor.h"
#include "DriverDistanceSensorUltrasonic.h"
#include "DriverDistanceSensorInfrared.h"
 
#define SPEAKER_PIN                             (9)

#define FIRST_LED_PIN                           (10)
#define FIRST_TRIG_PIN                          (11)
#define FIRST_ECHO_PIN                          (12)

#define SECOND_LED_PIN                          (4)
#define SECOND_TRIG_PIN                         (5)
#define SECOND_ECHO_PIN                         (6)

#define ANALOG_PIN                              (0)

#define MAX_DISTANCE                            (3000)    // in mm

#define MOTION_SENSOR_COUNT                     (3)
#define ULTRASONIC_MOTION_SENSOR_COUNT          (2)
#define INFRARED_MOTION_SENSOR_COUNT            (1)


#define LED_COUNT                               (2)


enum
{
  FIRST  = 0, 
  SECOND = 1,
  THIRD  = 2,
};

ControllerLed                  leds[LED_COUNT] ={
                                        ControllerLed(FIRST_LED_PIN),
                                        ControllerLed(SECOND_LED_PIN),
                                       };

ControllerSpeaker              speaker(SPEAKER_PIN);

DistanceIndicatorLed             distanceIndicatorLeds[LED_COUNT];

DistanceIndicatorSpeaker         distanceIndicatorSpeaker;

DriverDistanceSensorUltrasonic   distanceSensorsUltrasonic[ULTRASONIC_MOTION_SENSOR_COUNT] = {
                                                         DriverDistanceSensorUltrasonic(FIRST_TRIG_PIN,  FIRST_ECHO_PIN),        
                                                         DriverDistanceSensorUltrasonic(SECOND_TRIG_PIN, SECOND_ECHO_PIN)
                                                         };

DriverDistanceSensorInfrared     distanceSensorsInfrared[INFRARED_MOTION_SENSOR_COUNT]     = {
                                                         DriverDistanceSensorInfrared(ANALOG_PIN)
                                                         };

DistanceSensor                   distanceSensors[MOTION_SENSOR_COUNT] = {
                                                         DistanceSensor(&distanceSensorsUltrasonic[FIRST]), 
                                                         DistanceSensor(&distanceSensorsUltrasonic[SECOND]),
                                                         DistanceSensor(&distanceSensorsInfrared[FIRST])
                                                         };

DistanceSensorHandlerDispatcher  distanceSensorHandlerDispatchers[MOTION_SENSOR_COUNT]; 

ProcessDispatcher              processDispatcher;

LiquidCrystal_I2C newScreen(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

DistanceIndicatorScreen screen;

void setup()
{ 
  Serial.begin (9600);
   
  screen.attachScreen(&newScreen);
  
  processDispatcher.addSubProcess(&distanceSensors[FIRST]);
  processDispatcher.addSubProcess(&distanceSensors[SECOND]);
  processDispatcher.addSubProcess(&distanceSensors[THIRD]);
  processDispatcher.addSubProcess(&leds[FIRST]);
  processDispatcher.addSubProcess(&leds[SECOND]);
  processDispatcher.addSubProcess(&speaker);
  processDispatcher.addSubProcess(&screen);
  
  processDispatcher.setup();
  
  distanceIndicatorLeds[FIRST].attachLed(&leds[FIRST]);
  distanceIndicatorLeds[SECOND].attachLed(&leds[SECOND]);
  distanceIndicatorSpeaker.attachSpeaker(&speaker);
  
  distanceSensors[FIRST].setHandler(&distanceSensorHandlerDispatchers[FIRST]);
  distanceSensors[SECOND].setHandler(&distanceSensorHandlerDispatchers[SECOND]);
  distanceSensors[THIRD].setHandler(&distanceSensorHandlerDispatchers[THIRD]);
  
  distanceSensorHandlerDispatchers[FIRST].addSubHandler(&distanceIndicatorLeds[FIRST]);
  distanceSensorHandlerDispatchers[FIRST].addSubHandler(&distanceIndicatorSpeaker);
  distanceIndicatorSpeaker.startListenDistanceSensor(&distanceSensors[FIRST]);

  distanceSensorHandlerDispatchers[SECOND].addSubHandler(&distanceIndicatorLeds[SECOND]);
  distanceSensorHandlerDispatchers[SECOND].addSubHandler(&distanceIndicatorSpeaker);
  distanceIndicatorSpeaker.startListenDistanceSensor(&distanceSensors[SECOND]);

  distanceSensorHandlerDispatchers[THIRD].addSubHandler(&distanceIndicatorLeds[THIRD]);
  distanceSensorHandlerDispatchers[THIRD].addSubHandler(&distanceIndicatorSpeaker);
  distanceIndicatorSpeaker.startListenDistanceSensor(&distanceSensors[THIRD]);

  screen.addDistanceSensorToListen(&distanceSensors[FIRST], FIRST);
  screen.addDistanceSensorToListen(&distanceSensors[SECOND], SECOND);
  screen.addDistanceSensorToListen(&distanceSensors[THIRD], THIRD);
}

void loop()
{  
  processDispatcher.loop();
}

