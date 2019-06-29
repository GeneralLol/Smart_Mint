/*
 * Defines moisture sensor class, which represents a moisture sensor.
 */

#pragma once

#include <Arduino.h>

 class MoistureSensor{
   int pin;
   double reading;
   const static int MOISTURE_MAX = 1800;
   const static int MOISTURE_MIN = 2047;
 public:
   MoistureSensor(int pin, int analogRes);
   double read();
 }; 
