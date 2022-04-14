#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"

/**
 * Temperature sensor class
 **/
class temperature : public sensor {

public:
    std::string TYPE[3] = 
   {
      "HOT",
      "COLD",
      "NORMAL"
   };
    temperature(): sensor(ADS1115settings::AIN3){

    }
    void setTemperature(float voltage);
    float getTemperature();
    void setType(std::string type);
    std::string getType();
    void calcThreshold() override;
private:
    float temperature_;
    std::string type_;
};


#endif