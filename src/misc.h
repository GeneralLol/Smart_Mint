/*
 * Header for miscellaneous functions so that main.cpp would look nicer.
*/
#pragma once

void sensor_setup(int analogRes);
void blynk_setup(char auth[], char ssid[], char pass[]);
double moisture_percentage();
