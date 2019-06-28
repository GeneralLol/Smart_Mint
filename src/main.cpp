#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//The drier it is, the larger the number.
#define MOISTURE_MIN 2047
#define MOISTURE_MAX 1800

#define MOISTURE_SENSOR 35
#define WATER_THREASHOLD 0.6

void sensor_setup(int analogRes);
void blynk_setup(char auth[], char ssid[], char pass[]);
double moisture_percentage();

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  int analogRes = 11;

  sensor_setup(analogRes);
  Serial.println("Sensor setup complete.");

  char auth[] = "a4a0cb84512644459ff1c00440d69412";
  char ssid[] = "Stanford Residences";
  char pass[] = "";
  blynk_setup(auth, ssid, pass);

  Serial.println("Blynk started.");

}

void loop() {
  Blynk.run();

  double reading = moisture_percentage();

  Serial.println (reading);

  if (reading < WATER_THREASHOLD){
    digitalWrite (LED_BUILTIN, 1);
  }else{
    digitalWrite (LED_BUILTIN, 0);
  }

  //TODO: Implement push notification when mint needs watering.
  //Notify only once when the plant needs watering, and refresh the variable
  //next time when it is watered.

}

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
