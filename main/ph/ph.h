#ifndef __PH_H
#define __PH_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"
/**
 * pH sensor class
 **/
class ph : public sensor {

public:
    public:
    ph(): sensor("ph", ADS1115settings::AIN1){

    }
    
    void calcThreshold() override;
private:
};


#endif