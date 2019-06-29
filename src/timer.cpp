/*
 *  Implementation of the timer class.
 */

 #include <Arduino.h>

 #include "timer.h"

 Timer::Timer(){
   this->recordedTime = millis();
   this->currentTime  = millis();
 }

long Timer::get_recorded_time(){
  return this->recordedTime;
}

long Timer::refresh_recorded_time(){
  this->recordedTime = millis();
  return this->currentTime;
}

long Timer::get_delta_time(){
  currentTime = millis();
  //Serial.println(currentTime);
  return this->currentTime -this->recordedTime;
}
