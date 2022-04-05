#ifndef __PH_H
#define __PH_H

/*
 * pH Sensor Class
 *
 */
#include <assert.h>
#include "sensor.h"

/**
 * pH sensor class
 **/
class pH : public sensor {

public:
    pH(){

    }

    virtual void calcThreshold();

private:
   sensor pH_{"pH"};
};


#endif