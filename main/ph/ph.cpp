#include "ph.h"

void ph::setType(std::string type){
    type_ = type;
}

std::string ph::getType(){
    return type_;
}

void ph::calcThreshold(){
    for(auto& v:getData()) {
    if(v > 0.4){
        setType(ph::TYPE[1]);
    }else if(v < 0.3){
        setType(ph::TYPE[0]);
    }else{
        setType(ph::TYPE[2]);
    }
}
}

