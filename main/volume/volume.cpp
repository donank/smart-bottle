#include "volume.h"

bool volume::waterDetected(){
    return waterDetected_;
}

void volume::calcThreshold(){
    float latestValue = getData().front();
    if(latestValue > 0.4){
        waterDetected_ = true;
    }else if(latestValue < 0.3){
        waterDetected_ = false;
    }
}