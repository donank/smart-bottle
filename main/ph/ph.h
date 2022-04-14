#ifndef __PH_H
#define __PH_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"
/**
 * pH sensor class
 **/
class ph : public sensor {

public:
std::string TYPE[3] = 
   {
      "ACID",
      "BASE",
      "NEUTRAL"
   };

    ph(): sensor(ADS1115settings::AIN1){

    }
    
    void setType(std::string type);
    std::string getType();
    void calcThreshold() override;
    
private:
    std::string type_;
};


#endif