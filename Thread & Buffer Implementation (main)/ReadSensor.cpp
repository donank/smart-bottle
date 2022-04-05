#include "ReadSensor.h"
#include <chrono>


class work : public PutSensor {
	virtual void hasSample(float v) {

		Circularbuffer<double> cb1(10);
		Circularbuffer<double> cb2(10);
		Circularbuffer<double> cb3(10);
		Circularbuffer<double> cb4(10);

		using std::chrono::system_clock;
		std::time_t start_time = system_clock::to_time_t(system_clock::now());

		while (std::chrono::duration<double, std::milli>(system_clock::to_time_t(system_clock::now()) - start_time).count() == 10) {
			for (int i = 0; i < 4; i++) {
		
				printf("Channel: %d\n", i + 1);
				printf("%e\n", v);
				switch (i) {
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
		printf("%u", cb4.size());


	}
};


void ReadSensor::run()
{
	// Running is set to true
	running = 1;

	// Runs the Thread
	while (running)
	{
		 // Only extract data when buffer isn't empty
		if (!cb1d->empty() && !cb2d->empty() && !cb3d->empty() && !cb4d->empty()) {

			adc = (double)cb1d->get();
			cout << adc << endl;

			adc2 = (double)cb2d->get();
			cout << adc2 << endl;

			adc3 = (double)cb3d->get();
			cout << adc3 << endl;

			adc4 = (double)cb4d->get();
			cout << adc4 << endl;

			this_thread::sleep_for(chrono::milliseconds(5000));


			if (adc > 1 && adc2 > 2 && adc3 < 2 && adc4 > 4)
			{
				cout << "\nWater is Pure\n" << endl;
			}
			else {
				cout << "\nWater is Dirty\n" << endl;
			}

			cout << "\nOutcome Generated\n" << endl;

		}
		else
		{
			cout << "\nBuffer is Empty\n" << endl;
			this_thread::sleep_for(chrono::milliseconds(5000));
			//stop();
		}

	}

}



void ReadSensor::stop()
{
	running = 0;
	//uthread->join();
	//delete uthread;
	//uthread = NULL;
}


