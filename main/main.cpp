#include <iostream>
#include "ads1115rpi.h"
#include <chrono>
#include "ph.h"
#include "turbidity.h"
#include<thread>
#include<unistd.h>

ph ph;
turbidity tb;

class ADS1115Printer : public ADS1115rpi {
	/*
	virtual void hasSample(float v) {

	
		using std::chrono::system_clock;
        std::time_t start_time = system_clock::to_time_t (system_clock::now());
		printf("start time: \n: %d", start_time);
		int flag = 1;
		while(flag){

			std::time_t curr_time = system_clock::to_time_t (system_clock::now());

			if(curr_time - start_time == 20){
				flag = 0;
				printf("\ncb1-1: %e", ph.getData());
				printf("------------------------- \n");
				stop();
			}
			for(int i=0; i < 10; i++){
				//setChannel(ADS1115settings::Input::AIN0);
				ph.setData(v);
				printf("\n\t ph put1: %e", v);
				/*
				//setChannel(getChannel(i));
				ADS1115settings::Input channel = getChannel(i);
				//printf("\nChannel: %d",getChannel(i));
				switch(channel){
					case ADS1115settings::Input::AIN0: setChannel(channel);
					ph.setData(v);
					printf("\n\t ph put1: %e", v);
					break;
					case ADS1115settings::Input::AIN1: setChannel(channel);
					tb.setData(v);
					printf("\n\t tb put2: %e", v);
					break;
					case ADS1115settings::Input::AIN2: setChannel(channel);
					ph.setData(v);
					printf("\n\t ph put3: %e", v);
					break;
					case ADS1115settings::Input::AIN3: setChannel(channel);
					tb.setData(v);
					printf("\n\t tb put4: %e", v);
					break;
				}
				
				unsigned int microsecond = 1000000;
				usleep(1 * microsecond);

			}
		}
		
	}
	*/

	virtual void hasSample(float v){
		ph.setData(v);
		printf("\n\t ph put1: %e", v);
	}
};

int main() {
    fprintf(stderr,"Press any key to stop.\n");
	ADS1115Printer ads1115rpi;
    ADS1115settings s;
	s.samplingRate = ADS1115settings::FS860HZ;
	for(ADS1115settings::Input i=ADS1115settings::AIN0; i < ADS1115settings::AIN3; i = ADS1115settings::Input(i+1)){
		while(ph.getSize() != 10){
			s.channel = i;
			ads1115rpi.start(s);
			fprintf(stderr,"channel = %d\n",ads1115rpi.getADS1115settings().channel); 
    		fprintf(stderr,"fs = %d\n",ads1115rpi.getADS1115settings().getSamplingRate()); 
			ads1115rpi.stop();
		}
		ph.reset();
	}
	
	return 0;
}