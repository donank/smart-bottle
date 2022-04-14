#include "temperature.h"

void temperature::setTemperature(float voltage){
    temperature_ = voltage;
}

float temperature::getTemperature(){
    return temperature_;
}

void temperature::setType(temperature::TYPE type){
    type_ = type;
}

temperature::TYPE temperature::getType(){
    return type_;
}


void temperature::calcThreshold(){
    float latestValue = getData().front();
    if(latestValue > 0.4){
        setType(temperature::TYPE::HOT);
    }else if(latestValue < 0.3){
        setType(temperature::TYPE::COLD);
    }else{
        setType(temperature::TYPE::NORMAL);
    }
}