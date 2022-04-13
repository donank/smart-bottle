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

size_t sensor::getSize(){
    return cb_.size();
}

void sensor::reset(){
    cb_.reset();
}
