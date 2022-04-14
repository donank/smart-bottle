#ifndef __VOLUME_H
#define __VOLUME_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"

/**
 * Volume sensor class
 **/
class volume : public sensor {

public:
    public:
    volume(): sensor("volume", ADS1115settings::AIN0){

    }
    
    void calcThreshold() override;
private:
};


#endif