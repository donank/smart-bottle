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
enum TYPE
   {
      TRANSPARENT,
      TRANSLUSCENT,
      OPAQUE
   };
    turbidity(): sensor(ADS1115settings::AIN2){

    }
    void setType(turbidity::TYPE type);
    turbidity::TYPE getType();
    void calcThreshold() override;
private:
    turbidity::TYPE type_;
};


#endif