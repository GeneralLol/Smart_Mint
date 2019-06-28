/*
 * Definition for the sensor class, which contains name and readings from a
 * sensor.
*/
#include <string>

#include <Arduino.h>

#include "sensor.h"

class Sensor{
  string name;
  int pin;
  int reading;

public:
  Sensor();
  Sensor(const string&, int);


};
