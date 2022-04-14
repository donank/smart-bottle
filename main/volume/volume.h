#ifndef __VOLUME_H
#define __VOLUME_H

#include "../sensor/sensor.h"

/**
 * Volume sensor class
 **/
class volume : public sensor {

public:
    public:
    volume(): sensor("volume", 0){

    }
    
    void calcThreshold() override;
private:
};


#endif