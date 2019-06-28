#include <vector>
#include <string>

#include "plant.h"
#include "sensor.h"

using namespace std;

Plant::Plant(){
  sensors = {};
}

Plant::Plant(std::vector<Sensor> v;){
  sensors = v;
}

vector<Sensor> Plant::get_sensors(){
  return sensors;
}

string get_reading(){

  return ""; 
}
