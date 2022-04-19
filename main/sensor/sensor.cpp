#include "sensor.h"
#include <chrono>
#include <thread>

void sensor::setData(float data){
    //cb_.put(data);
    values.push_back(data);
}

std::deque<float> sensor::getData(){
    return values; //returns last inserted value from buffer
}

size_t sensor::getSize(){
    return values.size();
}

void sensor::popFront(){
    values.pop_front();
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
        if(curr_time - start_time == 5){
				flag = 0;
                this->stop();
                //killThread();
        } 

    }

}   

void sensor::startThread(){
    this->CppThreadInterface::start();
    this->join();
}
/*
void sensor::killThread(){
    delete this;
}
*/
ADS1115settings::Input sensor::getChannel(){
    return channel_;
}

