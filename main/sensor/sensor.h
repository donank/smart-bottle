#ifndef __SENSOR_H
#define __SENSOR_H

/*
 * Parent Sensor Class
 *
 */
#include <assert.h>
#include "circularbufferinstantiated.h"


#define ISR_TIMEOUT 1000

/**
 * Parent sensor class
 **/
class sensor {

public:
    sensor(const std::string& name){
        sensorName = name;
    }

    void setData(double data);
    void getData();
    virtual void calcThreshold();

private:
   std::string sensorName;
   circularbufferinstantiated cb{10};
};


#endif