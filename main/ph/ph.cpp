#include "ph.h"

void ph::setType(ph::TYPE type){
    type_ = type;
}

ph::TYPE ph::getType(){
    return type_;
}

void ph::calcThreshold(){
    float latestValue = getData().front();
    if(latestValue > 0.4){
        setType(ph::TYPE::BASE);
    }else if(latestValue < 0.3){
        setType(ph::TYPE::ACID);
    }else{
        setType(ph::TYPE::NEUTRAL);
    }
}

