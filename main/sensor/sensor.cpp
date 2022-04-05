#include "sensor.h"

std::string sensor::getName(){
    return sensorName;
}

void sensor::setData(double data){
    cb.put(data);
}

double sensor::getData(){
    return cb.get(); //returns last inserted value from buffer
}

