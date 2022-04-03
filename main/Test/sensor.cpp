#include <iostream>
#include "ads1115rpi.h"
#include "circularbuffer/circularbuffer.h"
#include <chrono>

class ADS1115Printer : public ADS1115rpi {
	virtual void hasSample(float v) {

		Circularbuffer<double> cb1(10);
		Circularbuffer<double> cb2(10);
		Circularbuffer<double> cb3(10);
		Circularbuffer<double> cb4(10);

		using std::chrono::system_clock;
        std::time_t start_time = system_clock::to_time_t (system_clock::now());

		while(std::chrono::duration<double, std::milli>(system_clock::to_time_t (system_clock::now())-start_time).count() == 10){
			for(int i=0; i < 4; i++){
				setChannel(getChannel(i));
				printf("Channel: %d\n",i+1);
				printf("%e\n",v);
				switch(i){
					case 1: cb1.put(v);
					break;
					case 2: cb2.put(v);
					break;
					case 3: cb3.put(v);
					break;
					case 4: cb4.put(v);
					break;
				}
			}
		}

		printf("cb4 size!\n");
		printf("%u",cb4.size());
		
		
	}
};

int main() {
    fprintf(stderr,"Press any key to stop.\n");
	ADS1115Printer ads1115rpi;
    ADS1115settings s;
	s.samplingRate = ADS1115settings::FS64HZ;
	ads1115rpi.start(s);
    fprintf(stderr,"fs = %d\n",ads1115rpi.getADS1115settings().getSamplingRate()); 
	getchar();
	ads1115rpi.stop();
	return 0;
}