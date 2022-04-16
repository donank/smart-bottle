#ifndef __TURBIDITY_H
#define __TURBIDITY_H

/*
 * Turbidity Sensor Class
 *
 */
#include <assert.h>
#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"

/**
 * Turbidity sensor class
 **/
class turbidity : public sensor {

public:
std::string TYPE[3] = 
   {
      "TRANSPARENT",
      "TRANSLUSCENT",
      "OPAQUE"
   };
    turbidity(): sensor(ADS1115settings::AIN2){

    }
    void setType(std::string type);
    std::string getType();
    void calcThreshold() override;
private:
    std::string type_;
};


#endif