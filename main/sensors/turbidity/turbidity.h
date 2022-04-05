#ifndef __TURBIDITY_H
#define __TURBIDITY_H

/*
 * Turbidity Sensor Class
 *
 */
#include <assert.h>
#include "sensor.h"

/**
 * Turbidity sensor class
 **/
class turbidity : public sensor {

public:
    turbidity(){

    }

    virtual void calcThreshold();

private:
   sensor turbidity_{"turbidity"};
};


#endif