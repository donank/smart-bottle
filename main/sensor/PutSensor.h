#ifndef PutSensor_h
#define PutSensor_h

#include <csignal>
#include <iostream>
#include "Thread.h"
#include "RingBuffer.h"
#include "circularbuffer.h"


using namespace std;

class PutSensor : public Thread
{
public:

	PutSensor(Circularbuffer<double>* cb1, Circularbuffer<double>* cb2, Circularbuffer<double>* cb3, Circularbuffer<double>* cb4, int buffer_length)
	{
		cb1d = cb1;
		cb2d = cb2;
		cb3d = cb3;
		cb4d = cb4;

		cout << "\nCircular Buffer PUT thread initialised\n" << endl;
	}

	
	void stop();
	

private:



	Circularbuffer<double> *cb1d;
	Circularbuffer<double> *cb2d;
	Circularbuffer<double> *cb3d;
	Circularbuffer<double> *cb4d;




	// Thread function that overrides current state
	void run();
	
	// Thread status
	bool running;
	
};


#endif