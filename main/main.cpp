#include <iostream>
#include "ads1115rpi.h"
#include <chrono>
#include "ph.h"
#include "turbidity.h"

class ADS1115Printer : public ADS1115rpi {
	virtual void hasSample(float v) {

		ph ph;
		turbidity tb;

		using std::chrono::system_clock;
        std::time_t start_time = system_clock::to_time_t (system_clock::now());
		printf("start time: \n: %d", start_time);
		int flag = 1;
		while(flag){

			std::time_t curr_time = system_clock::to_time_t (system_clock::now());
			printf("\ntime delay: %d", curr_time - start_time);

			if(curr_time - start_time == 4){
				flag = 0;
				printf("\ncb1-1: %e", ph.getData());
				printf("------------------------- \n");
				stop();
			}
			for(int i=0; i < 4; i++){
				//setChannel(ADS1115settings::Input::AIN3);
				setChannel(getChannel(i));
				printf("\nChannel: %d",i+1);
				switch(i){
					case 1: ph.setData(v);
					printf("\n\t ph put: %e", v);
					break;
					case 2: tb.setData(v);
					printf("\n\t tb put: %e", v);
					break;
					case 3: ph.setData(v);
					printf("\n\t ph put: %e", v);
					break;
					case 4: tb.setData(v);
					printf("\n\t tb put: %e", v);
					break;
				}
			}
		}

		
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