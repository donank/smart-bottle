#include "temperature.h"

void temperature::setTemperature(float voltage){
    temperature_ = voltage;
}

float temperature::getTemperature(){
    return temperature_;
}

void temperature::setType(std::string type){
    type_ = type;
}

std::string temperature::getType(){
    return type_;
}


void temperature::calcThreshold(){
    for(auto& v:getData()) {
	    if(v > 0.4){
        setType(temperature::TYPE[0]);
    }else if(v < 0.3){
        setType(temperature::TYPE[1]);
    }else{
        setType(temperature::TYPE[2]);
    }	
	}
    
}