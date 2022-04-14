#ifndef __SENSOR_H
#define __SENSOR_H

/*
 * Parent Sensor Class
 *
 */
#include <assert.h>
#include "../circularbuffer/circularbuffer.h"
#include "CppThread.h"
#include "../ads1115rpi/ads1115rpi.h"

class CppThreadInterface : public CppThread{
protected:
    virtual void threadRun() = 0;
    void run() override
    {
        threadRun();
    }
};

/**
 * Parent sensor class
 **/
class sensor: public ADS1115rpi, CppThreadInterface {

public:
    sensor(const std::string& name, int channel){
        name_ = name;
        switch(channel){
            case 0: channel_ = ADS1115settings::AIN0;
            case 1: channel_ = ADS1115settings::AIN1;
            case 2: channel_ = ADS1115settings::AIN2;
            case 3: channel_ = ADS1115settings::AIN3;
        }
    }
    
    std::string getName();
    void setData(double data);
    double getData();
    size_t getSize();
    void reset();
    void startThread();
    virtual void calcThreshold() = 0;

private:
	void threadRun();

private:
   std::string name_;
   ADS1115settings::Input channel_;
   circularbuffer<double> cb_{10};
};


#endif