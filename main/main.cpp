#include <iostream>
#include "ads1115rpi.h"
#include "circularbufferinstantiated.h"
#include <chrono>

class ADS1115Printer : public ADS1115rpi {
	virtual void hasSample(float v) {

	    circularbufferinstantiated cb1(10);
		circularbufferinstantiated cb2(10);
		circularbufferinstantiated cb3(10);
		circularbufferinstantiated cb4(10);

		using std::chrono::system_clock;
        std::time_t start_time = system_clock::to_time_t (system_clock::now());
		printf("start time: \n: %d", start_time);
		int flag = 1;
		while(flag){
			printf("\n\tcb1 size: %zu", cb1.size());

			std::time_t curr_time = system_clock::to_time_t (system_clock::now());
			printf("\ntime delay: %d", curr_time - start_time);

			if(curr_time - start_time == 4){
				flag = 0;
				printf("\ncb1-1: %e", cb1.get());
				printf("\ncb1-2: %e", cb1.get());
				printf("\ncb1-3: %e", cb1.get());
				printf("\ncb1-4: %e", cb1.get());
				printf("\ncb1 size: %zu", cb1.size());
				printf("------------------------- \n");
				stop();
			}
			for(int i=0; i < 4; i++){
				//setChannel(ADS1115settings::Input::AIN3);
				setChannel(getChannel(i));
				printf("\nChannel: %d",i+1);
				switch(i){
					case 1: cb1.put(v);
					printf("\n\tcb1 put: %e", v);
					break;
					case 2: cb2.put(v);
					printf("\n\tcb2 put: %e", v);
					break;
					case 3: cb3.put(v);
					printf("\n\tcb3 put: %e", v);
					break;
					case 4: cb4.put(v);
					printf("\n\tcb4 put: %e", v);
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