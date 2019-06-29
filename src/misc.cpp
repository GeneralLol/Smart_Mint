#include <Arduino.h>

#include "misc.h"

void sensor_setup(int analogRes){
  analogReadResolution(analogRes);
  analogSetAttenuation(ADC_6db);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOISTURE_SENSOR, INPUT);
}

void blynk_setup(char auth[], char ssid[], char pass[]){
  Blynk.begin(auth, ssid, pass);
}

double moisture_percentage(){
  int readingRaw = analogRead (MOISTURE_SENSOR);
  double percentage = double(readingRaw - MOISTURE_MIN)
                    / double(MOISTURE_MAX - MOISTURE_MIN);
  return percentage;
}
