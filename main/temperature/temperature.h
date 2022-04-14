#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"

/**
 * Temperature sensor class
 **/
class temperature : public sensor {

public:
    public:
    temperature(): sensor("temperature", ADS1115settings::AIN3){

    }
    
    void calcThreshold() override;
private:
};


#endif