#include "sensor.h"

std::string sensor::getName(){
    return sensorName;
}

void sensor::setData(double data){
    cb_.put(data);
}

double sensor::getData(){
    return cb_.get(); //returns last inserted value from buffer
}

