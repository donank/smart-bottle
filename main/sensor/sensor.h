#ifndef __SENSOR_H
#define __SENSOR_H

/*
 * Parent Sensor Class
 *
 */
#include <assert.h>
#include "circularbufferinstantiated.h"

/**
 * Parent sensor class
 **/
class sensor {

public:
    sensor(const std::string& name){
        sensorName = name;
    }

    std::string getName();
    void setData(double data);
    double getData();
    virtual void calcThreshold();

private:
   std::string sensorName;
   circularbufferinstantiated cb{10};
};


#endif