#ifndef __PH_H
#define __PH_H

#include "../sensor/sensor.h"

/**
 * pH sensor class
 **/
class ph : public sensor {

public:
    public:
    ph(): sensor("ph", 1){

    }
    
    void calcThreshold() override;
private:
};


#endif