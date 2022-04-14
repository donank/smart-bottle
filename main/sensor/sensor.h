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
#include<unistd.h>
#include <deque>

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
    sensor(const std::string& name, ADS1115settings::Input channel){
        name_ = name;
        channel_ = channel;
    }
    
    std::string getName();
    ADS1115settings::Input getChannel();
    void setData(float data);
    std::deque<float> getData();
    void popFront();
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
   std::deque<float> values;
};


#endif