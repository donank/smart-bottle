#include <iostream>
#include <Thread>
#include "circularbuffer/circularbuffer.h"
#include "circularbuffer/circularbuffer.cpp"
#include "PutSensor.h"
#include "PutSensor.cpp"
#include "ReadSensor.h"
#include "ReadSensor.cpp"
#include "Demo.h"
#include "Demo.cpp"
#include "Demo2.h"
#include "Demo2.cpp"
//#include "adc1115.cpp"

using namespace std;

//Thread T1;
int main()
{


    Circularbuffer<double> cb1(10);
    Circularbuffer<double> cb2(10);
    Circularbuffer<double> cb3(10);
    Circularbuffer<double> cb4(10);
    


    //DemoThread demoThread1(0);
    //DemoThread2 demoThread2(0);

    //demoThread1.start();
    //demoThread2.start();

    //demoThread1.join();
    //demoThread2.join();


    // Initialize Put and Read Threads
    PutSensor PutThread(&cb1, &cb2, &cb3, &cb4, 2);
    ReadSensor ReadThread(&cb1, &cb2, &cb3, &cb4, 2);


    PutThread.start();
    ReadThread.start();

    PutThread.join();
    ReadThread.join();

    
   
    
}

