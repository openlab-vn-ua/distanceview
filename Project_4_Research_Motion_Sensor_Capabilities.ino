#include <Arduino.h>

#include "Led.h"
#include "MotionIndicatorLedAndSpeaker.h"
#include "MotionSensor.h"
#include "Process.h"
#include "Speaker.h"
#include "MotionIndicatorScreen.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define SPEAKER_PIN                             (9)

#define FIRST_LED_PIN                            (10)
#define FIRST_TRIG_PIN                           (11)
#define FIRST_ECHO_PIN                           (12)

#define SECOND_LED_PIN                           (4)
#define SECOND_TRIG_PIN                          (5)
#define SECOND_ECHO_PIN                          (6)

#define ANALOG_PIN                              (0)

#define MAX_DISTANCE                            (3000)    // in mm

#define MOTION_SENSOR_COUNT                     (1)
#define ULTRASONIC_MOTION_SENSOR_COUNT          (2)
#define INFRARED_MOTION_SENSOR_COUNT            (1)


#define LED_COUNT                               (2)


enum
{
  FIRST  = 0, 
  SECOND = 1,
  THIRD  = 2,
};

Led                            leds[LED_COUNT] ={
                                        Led(FIRST_LED_PIN),
                                        Led(SECOND_LED_PIN),
                                       };

Speaker                        speaker(SPEAKER_PIN);

MotionIndicatorLed             motionIndicatorLeds[LED_COUNT];

MotionIndicatorSpeaker         motionIndicatorSpeaker;

UltrasonicMotionSensorDriver   ultrasonicMotionSensors[ULTRASONIC_MOTION_SENSOR_COUNT] = {
                                                         UltrasonicMotionSensorDriver(FIRST_TRIG_PIN,  FIRST_ECHO_PIN),        
                                                         UltrasonicMotionSensorDriver(SECOND_TRIG_PIN, SECOND_ECHO_PIN)
                                                         };

InfraredMotionSensorDriver     infraredMotionSensors[INFRARED_MOTION_SENSOR_COUNT]     = {
                                                         InfraredMotionSensorDriver(ANALOG_PIN)
                                                         };

MotionSensor                   motionSensors[MOTION_SENSOR_COUNT] = {
                                                         MotionSensor(&infraredMotionSensors[FIRST])
                                                         };

MotionSensorHandlerDispatcher  motionSensorHandlerDispatchers[MOTION_SENSOR_COUNT]; 

ProcessDispatcher              processDispatcher;

LiquidCrystal_I2C newScreen(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

MotionIndicatorScreen screen;

void setup()
{ 
  Serial.begin (9600);
   
  screen.attachScreen(&newScreen);
  
  processDispatcher.addSubProcess(&motionSensors[FIRST]);
  processDispatcher.addSubProcess(&leds[FIRST]);
  processDispatcher.addSubProcess(&speaker);
  processDispatcher.addSubProcess(&screen);
  
  processDispatcher.setup();
  
  motionIndicatorLeds[FIRST].attachLed(&leds[FIRST]);
  motionIndicatorLeds[SECOND].attachLed(&leds[SECOND]);
  motionIndicatorSpeaker.attachSpeaker(&speaker);
  
  motionSensors[FIRST].setHandler(&motionSensorHandlerDispatchers[FIRST]);
  
  motionSensorHandlerDispatchers[FIRST].addSubHandler(&motionIndicatorLeds[FIRST]);
  motionSensorHandlerDispatchers[FIRST].addSubHandler(&motionIndicatorSpeaker);
  motionIndicatorSpeaker.startListenMotionSensor(&motionSensors[FIRST]);

  screen.addMotionSensorToListen(&motionSensors[FIRST], FIRST);
}

void loop()
{  
  processDispatcher.loop();
}

