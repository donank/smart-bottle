#include "PutSensor.h"
#include <iostream>
#include <chrono>

using namespace std;


// Overloads the worker thread. The purpose of this is to test the functionalities of both thread and circular buffer
void PutSensor::run()
{
	// Running is set to true
	running = 1;
	
	// Runs the Thread
	while (running)
	{
		 // Only put data when buffer isn't full
		if (!cb1d->full() && !cb2d->full() && !cb3d->full() && !cb4d->full()) {

			cb1d->put(2.01);
			cb2d->put(78.4);
			cb3d->put(45.7);
			cb4d->put(14.8);

			this_thread::sleep_for(chrono::milliseconds(5000));

			cb1d->put(7.4);
			cb2d->put(56.8);
			cb3d->put(3.5);
			cb4d->put(2.4);

			this_thread::sleep_for(chrono::milliseconds(5000));

			cb1d->put(8.9);
			cb2d->put(65.7);
			cb3d->put(0.24);
			cb4d->put(4.8);

			this_thread::sleep_for(chrono::milliseconds(2000));
			cout << "\nData transfered into Buffer\n" << endl;
			this_thread::sleep_for(chrono::milliseconds(10000));

			cb1d->put(7.4);
			cb2d->put(56.8);
			cb3d->put(3.5);
			cb4d->put(2.4);

			this_thread::sleep_for(chrono::milliseconds(5000));

			cb1d->put(77.4);
			cb2d->put(6.8);
			cb3d->put(0.5);
			cb4d->put(9.4);

			stop();

		}
		else
		{
			cout << "\nBuffer is full\n" << endl;
			this_thread::sleep_for(chrono::milliseconds(5000));
			stop();
		}

	}

}

// Stops the funtion
void PutSensor::stop()
{
	    running = 0;
	    //uthread->join();
		//delete uthread;
		//uthread = NULL;

}

