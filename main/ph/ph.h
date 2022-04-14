#ifndef __PH_H
#define __PH_H

#include "../sensor/sensor.h"
#include "../ads1115rpi/ads1115rpi.h"
/**
 * pH sensor class
 **/
class ph : public sensor {

public:
    enum TYPE
   {
      ACID,
      BASE,
      NEUTRAL
   };

    ph(): sensor(ADS1115settings::AIN1){

    }
    
    void setType(ph::TYPE type);
    ph::TYPE getType();
    void calcThreshold() override;
    
private:
    ph::TYPE type_;
};


#endif