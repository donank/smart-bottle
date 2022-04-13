#ifndef __TURBIDITY_H
#define __TURBIDITY_H

/*
 * Turbidity Sensor Class
 *
 */
#include <assert.h>
#include "../sensor/sensor.h"

/**
 * Turbidity sensor class
 **/
class turbidity : public sensor {

public:
    turbidity(): sensor("turbidity"){

    }
    
    void calcThreshold() override;
private:

};


#endif