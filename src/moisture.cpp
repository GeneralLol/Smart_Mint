/*
 * Implementation of moisture sensor class.
 */

#include <Arduino.h>

#include <moisture.h>

MoistureSensor::MoistureSensor(int pin, int analogRes){
  analogReadResolution(analogRes);
  analogSetAttenuation(ADC_6db);
  this->pin = pin;
  pinMode(pin, INPUT);
}

double MoistureSensor::read(){
  int readingRaw = analogRead (this->pin);
  this->reading = double(readingRaw - MOISTURE_MIN)
                    / double(MOISTURE_MAX - MOISTURE_MIN);
  return this->reading;
}
