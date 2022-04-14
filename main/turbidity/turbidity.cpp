#include "turbidity.h"

void turbidity::setType(std::string type){
    type_ = type;
}
    
std::string turbidity::getType(){
    return type_;
}

void turbidity::calcThreshold(){
    float latestValue = getData().front();
    if(latestValue > 0.4){
        setType(turbidity::TYPE[2]);
    }else if(latestValue < 0.3){
        setType(turbidity::TYPE[0]);
    }else{
        setType(turbidity::TYPE[1]);
    }
}
