#ifndef __SENSOR_H
#define __SENSOR_H

/*
 * Parent Sensor Class
 *
 */
#include <assert.h>
#include "circularbuffer.h"

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
    size_t getSize();
    void reset();
    virtual void calcThreshold() = 0;

private:
   std::string sensorName;
   circularbuffer<double> cb_{10};
};


#endif