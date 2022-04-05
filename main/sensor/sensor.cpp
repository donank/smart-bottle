#include "sensor.h"

void sensor::setData(double data){
    cb.put(data);
}

double sensor::getData(){
    return cb.get(); //returns last inserted value from buffer
}

