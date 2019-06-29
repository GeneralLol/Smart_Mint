#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "timer.h"
#include "moisture.h"

//The drier it is, the larger the number.
#define MOISTURE_MIN 2047
#define MOISTURE_MAX 1800

const static int MOISTURE_SENSOR_PIN   = 35;     //Pin for the moisture sensor.
const static double WATER_THREASHOLD   = 0.1;    //Threashold which the system notiifes to water.
const static int DEBUG_SERIAL_INTERVAL = 500;    //intervals in miliseconds which the chip sends info to Serial.
const static int ANALOG_RESOLUTION     = 11;


//Global vars needed to get info around.
static Timer* timer = new Timer();
static MoistureSensor* moistureSensor = new MoistureSensor (MOISTURE_SENSOR_PIN, ANALOG_RESOLUTION);

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  Serial.println("Sensor setup complete.");

  char auth[] = "a4a0cb84512644459ff1c00440d69412";
  char ssid[] = "Stanford Residences";
  char pass[] = "";

  Serial.println("Starting Blynk. . .");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Blynk started.");

}

void loop() {
  Blynk.run();

  double reading = moistureSensor->read();

  //Serial.println(timer.get_delta_time());
  //See timer.cpp for implementation of get_delta_time and refresh_recorded_time.
  if (timer->get_delta_time() >= DEBUG_SERIAL_INTERVAL){
    Serial.println (reading);
    timer->refresh_recorded_time();
  }

  if (reading < WATER_THREASHOLD){
    digitalWrite (LED_BUILTIN, 1);
  }else{
    digitalWrite (LED_BUILTIN, 0);
  }

  //TODO: Implement push notification when mint needs watering.
  //Notify only once when the plant needs watering, and refresh the variable
  //next time when it is watered.

}
