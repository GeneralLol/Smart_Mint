/*
 * Definition for the plant class, which contains all of the sensor information
 * coming from one pot.
*/

#include <vector>
#inlcude <string>

#include "sensor.h"

class Plant{
  std::vector<Sensor> sensors;
public:
  Plant();
  Plant(std::vector<Sensor>&);

  std::vector<Sensor> get_sensors();  //Returns the vector of sensors.
  std::string get_reading();          //Returns a formatted reading of all of the
                                      //sensors attached to the plant.
}; 
