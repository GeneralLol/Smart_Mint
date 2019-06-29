#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "timer.h"
#include "moisture.h"
#include "notification.h"

//The drier it is, the larger the number.
#define MOISTURE_MIN 2047
#define MOISTURE_MAX 1800

const static int MOISTURE_SENSOR_PIN   = 35;     //Pin for the moisture sensor.
const static double WATER_THREASHOLD   = 0.1;    //Threashold which the system notiifes to water.
const static int DEBUG_SERIAL_INTERVAL = 3000;   //intervals in miliseconds which the chip sends info to Serial.
const static int ANALOG_RESOLUTION     = 11;
const static int NOTIFICATION_INTERVAL = 3600000;//intervals in miliseconds for phone push notifications.


//Global vars needed to get info around.
static Timer* debugTimer = new Timer();           //Used to time debug messages from Serial.
static Timer* notificationTimer = new Timer();    //Used to buffer between dropping below threashold humidity and resetting the notification flag.
static MoistureSensor* moistureSensor = new MoistureSensor (MOISTURE_SENSOR_PIN, ANALOG_RESOLUTION);
static Notification* notification = new Notification("Water your mint!");
static WidgetTerminal terminal(V0);

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

  Blynk.notify("Smart Mint Online.");
}

void loop() {
  Blynk.run();

  double reading = moistureSensor->read();

  //Serial.println(timer.get_delta_time());
  //See timer.cpp for implementation of get_delta_time and refresh_recorded_time.
  if (debugTimer->get_delta_time() >= DEBUG_SERIAL_INTERVAL){
    Serial.println (reading);
    debugTimer->refresh_recorded_time();
    Blynk.virtualWrite(V1, reading * 100);
  }
  //1. When water level is low, send notification, set LED on.
  //2. After the notification is sent, do not send again until the plant is watered,
  //  or for an extented period of time.
  //3. When the plat is watered again(humidity higher than threashold), reset notification
  //  and turn LED off.
  int notificationDeltaT = notificationTimer->get_delta_time();
  if (reading < WATER_THREASHOLD && !notification->flag
      && notificationDeltaT > NOTIFICATION_INTERVAL){
    Blynk.notify(notification->message.c_str());
    notification->flag = 1;
    notificationTimer->refresh_recorded_time();
  }

  if (reading > WATER_THREASHOLD){
    digitalWrite (LED_BUILTIN, 0);
  }

  if (reading < WATER_THREASHOLD){
    digitalWrite (LED_BUILTIN, 1);
  }
}
