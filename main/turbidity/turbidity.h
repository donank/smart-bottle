#ifndef __TURBIDITY_H
#define __TURBIDITY_H

/*
 * Turbidity Sensor Class
 *
 */
#include <assert.h>
#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"

/**
 * Turbidity sensor class
 **/
class turbidity : public sensor {

public:
    turbidity(): sensor("turbidity", ADS1115settings::AIN2){

    }
    
    void calcThreshold() override;
private:

};


#endif