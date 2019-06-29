/*
 * Definition for the Timer class which will be used in the main program to keep
 * track of time.
*/

#pragma once

#include <Arduino.h>

class Timer{
  long recordedTime;
  long currentTime;

public:
  Timer();

  long get_recorded_time();
  long refresh_recorded_time();
  long get_delta_time();
};
