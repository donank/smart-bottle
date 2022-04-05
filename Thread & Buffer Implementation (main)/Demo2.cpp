#include "Demo2.h"

#include <stdio.h>
#include <chrono>
#include <thread>
//#include "circularbuffer.h"


DemoThread2::DemoThread2(int _offset)
{
	//RingBuffer*adc1_addr;
	//adc1_data = RingBuffer[0];


	cout << "\nCircular Buffer GET thread initialised\n" << endl;

}

void DemoThread2::run()
{
	// at this point the thread has been started
	running = 1;

	// this is where we want to do stuff
	while (running)
	{
		for (int i = 0; i < 1; i++) 
		{
		
			//cb1.put(50);
			Circularbuffer<double> cb1(10);

			adc = cb1.get();
			cout << adc << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			adc = cb1.get();
			cout << adc << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			adc = cb1.get();
			cout << adc << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			adc = cb1.get();
			cout << adc << endl;

			adc = cb1.get();
			cout << adc << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			adc = cb1.get();
			cout << adc << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			adc = cb1.get();
			cout << adc << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			adc = cb1.get();
			cout << adc << endl;

			//cout << adc4 << endl;
			cout << "\nData extracted from Buffer\n" << endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			stop();
		}



	}

}



void DemoThread2::stop()
{
	running = 0;
	//uthread->join();
	//delete uthread;
	//uthread = NULL;

}
