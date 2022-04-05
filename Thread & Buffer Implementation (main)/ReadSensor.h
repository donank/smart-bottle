#ifndef READSENSOR
#define READSENSOR

#include <iostream>
#include "Thread.h"
#include "circularbuffer/circularbuffer.h"

using namespace std;

class ReadSensor : public Thread
{
public:

	ReadSensor(Circularbuffer<double>* cb1, Circularbuffer<double>* cb2, Circularbuffer<double>* cb3, Circularbuffer<double>* cb4, int buffer_size)
	{
		cb1d = cb1;
		cb2d = cb2;
		cb3d = cb3;
		cb4d = cb4;

		cout << "\nRead Sensor thread initialised\n" << endl;
	}

	void stop();

private:


	Circularbuffer<double>* cb1d;
	Circularbuffer<double>* cb2d;
	Circularbuffer<double>* cb3d;
	Circularbuffer<double>* cb4d;

	double adc, adc2, adc3, adc4;


	// Thread function that overrides current state
	void run();

	// Thread status
	bool running;
	
};

#endif
