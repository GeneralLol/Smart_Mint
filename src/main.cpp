#include <Arduino.h>

//#include "plant.h"

//The drier it is, the larger the number.
#define MOISTURE_MIN 2047
#define MOISTURE_MAX 1800

#define MOISTURE_SENSOR 35

void setup() {
  Serial.begin(9600);
  analogReadResolution(11);
  analogSetAttenuation(ADC_6db);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOISTURE_SENSOR, INPUT);
}

void loop() {

  int readingRaw = analogRead (MOISTURE_SENSOR);
  double percentage = double(readingRaw - MOISTURE_MIN)
                    / double(MOISTURE_MAX - MOISTURE_MIN);

  Serial.println (percentage);
  //Serial.println (percentage);

  if (percentage < 0.5){
    digitalWrite (LED_BUILTIN, 1);
  }else{
    digitalWrite (LED_BUILTIN, 0);
  }

  delay(1000); 
}
