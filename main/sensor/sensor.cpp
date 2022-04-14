#include "sensor.h"
#include <chrono>
#include <thread>

std::string sensor::getName(){
    return name_;
}

void sensor::setData(double data){
    cb_.put(data);
}

double sensor::getData(){
    return cb_.get(); //returns last inserted value from buffer
}

size_t sensor::getSize(){
    return cb_.size();
}

void sensor::reset(){
    cb_.reset();
}

void sensor::threadRun(){
    ADS1115settings s;
	s.samplingRate = ADS1115settings::FS8HZ;
    s.channel = channel_;
    using std::chrono::system_clock;
    std::time_t start_time = system_clock::to_time_t (system_clock::now());
    int flag = 1;
    while(flag){
        this->ADS1115rpi::start(s);
        std::time_t curr_time = system_clock::to_time_t (system_clock::now());
        if(curr_time - start_time == 20){
				flag = 0;
                this->stop();
        } 

    }

}   

void sensor::startThread(){
    this->CppThreadInterface::start();
    this->join();
}

