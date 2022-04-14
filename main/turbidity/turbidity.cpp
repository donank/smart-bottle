#include "turbidity.h"

void turbidity::setType(turbidity::TYPE type){
    type_ = type;
}
    
turbidity::TYPE turbidity::getType(){
    return type_;
}

void turbidity::calcThreshold(){
    float latestValue = getData().front();
    if(latestValue > 0.4){
        setType(turbidity::TYPE::OPAQUE);
    }else if(latestValue < 0.3){
        setType(turbidity::TYPE::TRANSPARENT);
    }else{
        setType(turbidity::TYPE::TRANSLUSCENT);
    }
}
