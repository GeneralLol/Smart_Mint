#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "timer.h"
#include "misc.h"

//The drier it is, the larger the number.
#define MOISTURE_MIN 2047
#define MOISTURE_MAX 1800

#define MOISTURE_SENSOR 35            //Pin for the moisture sensor.
#define WATER_THREASHOLD 0.3          //Threashold which the system notiifes to water.
#define DEBUG_SERIAL_INTERVAL 500     //intervals in miliseconds which the chip sends info to Serial.


void sensor_setup(int analogRes);
void blynk_setup(char auth[], char ssid[], char pass[]);
double moisture_percentage();

//Global vars needed to get info around.
Timer timer;

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  int analogRes = 11;

  sensor_setup(analogRes);
  Serial.println("Sensor setup complete.");

  char auth[] = "a4a0cb84512644459ff1c00440d69412";
  char ssid[] = "Stanford Residences";
  char pass[] = "";

  Serial.println("Starting Blynk. . .");
  blynk_setup(auth, ssid, pass);
  Serial.println("Blynk started.");

}

void loop() {
  Blynk.run();
  
  double reading = moisture_percentage();

  //Serial.println(timer.get_delta_time());
  //See timer.cpp for implementation of get_delta_time and refresh_recorded_time.
  if (timer.get_delta_time() >= DEBUG_SERIAL_INTERVAL){
    Serial.println (reading);
    timer.refresh_recorded_time();
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
