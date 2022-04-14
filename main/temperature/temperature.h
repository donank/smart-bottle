#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

#include "../sensor/sensor.h"

/**
 * Temperature sensor class
 **/
class temperature : public sensor {

public:
    public:
    temperature(): sensor("temperature", 3){

    }
    
    void calcThreshold() override;
private:
};


#endif