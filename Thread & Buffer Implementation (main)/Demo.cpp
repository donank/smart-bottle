#include "Demo.h"

#include <stdio.h>
#include <chrono>
#include <thread>
//#include "circularbuffer.h"


DemoThread::DemoThread(int _offset)
{
	//RingBuffer*adc1_addr;
	//adc1_data = RingBuffer[0];

	Circularbuffer<double> cb1(10);
	//cb1 = *b1;
	cout << "\nCircular Buffer PUT thread initialised\n" << endl;

}

void DemoThread::run()
{
	// at this point the thread has been started
	running = 1;

	// this is where we want to do stuff
	while (running)
	{
		for (int i = 0; i < 1; i++) 
		{
			
			Circularbuffer<double> cb1(10);
			cb1.put(50);
			cb1.put(40);
			cb1.put(30);
			cb1.put(20);
			cb1.put(10);
			cb1.put(5);
			cb1.put(5.2);
			cb1.put(4.3);
			cb1.put(2.5);
			cb1.put(9.2);
			cb1.put(7.2);
			cb1.put(5.4);


			//cout << adc4 << endl;
			cout << "\nData moved into Buffer\n" << endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			stop();
		}



	}

}



void DemoThread::stop()
{
	running = 0;
	//uthread->join();
	//delete uthread;
	//uthread = NULL;

}
