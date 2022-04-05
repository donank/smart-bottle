#ifndef DEMO_THREAD2_H
#define DEMO_THREAD2_H

#include "Thread.h"
#include "circularbuffer/circularbuffer.h"

class DemoThread2 : public Thread {

public:
	DemoThread2(int _offset);

private:
	void run();
	void stop();
	bool running;

private:
	int offset;
	double adc, adc2, adc3, adc4;

};

#endif