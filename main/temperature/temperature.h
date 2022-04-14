#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"

/**
 * Temperature sensor class
 **/
class temperature : public sensor {

public:
    enum TYPE
   {
      HOT,
      COLD,
      NORMAL
   };
    temperature(): sensor(ADS1115settings::AIN3){

    }
    void setTemperature(float voltage);
    float getTemperature();
    void setType(temperature::TYPE type);
    temperature::TYPE getType();
    void calcThreshold() override;
private:
    float temperature_;
    temperature::TYPE type_;
};


#endif