#include "volume.h"

bool volume::waterDetected(){
    return waterDetected_;
}

void volume::calcThreshold(){
for(auto& v:getData()) {
        if(v > 0.4){
        waterDetected_ = true;
    }else if(v < 0.3){
        waterDetected_ = false;
    }
}
}