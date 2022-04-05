#ifndef DEMO_THREAD_H
#define DEMO_THREAD_H

#include "Thread.h"
#include "circularbuffer/circularbuffer.h"

class DemoThread : public Thread {

public:
	DemoThread(int _offset);

private:
	void run();
	void stop();
	bool running;

private:
	int offset;
	double adc, adc2, adc3, adc4;
	double b1;

};

#endif