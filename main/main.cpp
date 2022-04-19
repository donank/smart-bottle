#include <iostream>
#include "ads1115rpi.h"
#include <chrono>
#include<thread>
#include<unistd.h>
#include "json_fastcgi_web_api.h"
#include <string.h>

#include "volume.h"
#include "ph.h"
#include "turbidity.h"
#include "temperature.h"

bool mainRunning = true;

/**
 * Handler when the user has pressed ctrl-C
 * send HUP via the kill command.
 **/
void sigHandler(int sig) { 
	if((sig == SIGHUP) || (sig == SIGINT)) {
		mainRunning = false;
	}
}


/** 
 * Sets a signal handler so that you can kill
 * the background process gracefully with:
 * kill -HUP <PID>
 **/
void setHUPHandler() {
	struct sigaction act;
	memset (&act, 0, sizeof (act));
	act.sa_handler = sigHandler;
	if (sigaction (SIGHUP, &act, NULL) < 0) {
		perror ("sigaction");
		exit (-1);
	}
	if (sigaction (SIGINT, &act, NULL) < 0) {
		perror ("sigaction");
		exit (-1);
	}
}
class ADS1115PrinterVM : public volume {
public:
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		setData(v);
		calcThreshold();
		if (getSize() > maxBufSize) popFront();
	}
	
	void forceValue(float a) {
		
		for(auto& v:getData()) {
			v = a;
		}
	}
};

class ADS1115PrinterPH : public ph {
public:
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		setData(v);
		calcThreshold();
		if (getSize() > maxBufSize) popFront();
	}
	
	void forceValue(float a) {

		for(auto& v:getData()) {
			v = a;
		}
	}
};

class ADS1115PrinterTB : public turbidity {
public:
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		setData(v);
		calcThreshold();
		if (getSize() > maxBufSize) popFront();
	}
	
	void forceValue(float a) {
	
		for(auto& v:getData()) {
			v = a;
		}
	}
};

class ADS1115PrinterTP : public temperature {
public:
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		setData(v);
		calcThreshold();
		if (getSize() > maxBufSize) popFront();
	}
	
	void forceValue(float a) {
	
		for(auto& v:getData()) {
			v = a;
		}
	}
};

/**
 * Callback handler which returns data to the
 * nginx server.
 **/
class JSONCGIADCCallback : public JSONCGIHandler::GETCallback {
private:
	/**
	 * Pointer to the ADC event handler because it keeps
	 * the data in this case. In a proper application
	 * that would be probably a database class or a
	 * controller keeping it all together.
	 **/
	ADS1115PrinterVM* sensorfastcgivm;
	ADS1115PrinterPH* sensorfastcgiph;
	ADS1115PrinterTB* sensorfastcgitb;
	ADS1115PrinterTP* sensorfastcgitp;

public:
	bool drinkable(ADS1115PrinterVM* argVM, ADS1115PrinterPH* argPH, 
	ADS1115PrinterTB* argTB, ADS1115PrinterTP* argTP){
		bool drinkable = false;
		if(argVM->waterDetected()){
			if(argPH->getType() == argPH->TYPE[2] && argTB->getType() == argTB->TYPE[0]){
				drinkable = true;
			}else{
				drinkable = false;
			}
		}else{
			drinkable = false;
		}
		return drinkable;
}
	/**
	 * Constructor: argument is the ADC callback handler
	 * which keeps the data as a simple example.
	 **/
	JSONCGIADCCallback(ADS1115PrinterVM* argSENSORfastcgivm, ADS1115PrinterPH* argSENSORfastcgiph, 
	ADS1115PrinterTB* argSENSORfastcgitb, ADS1115PrinterTP* argSENSORfastcgitp) {
		sensorfastcgivm = argSENSORfastcgivm;
		sensorfastcgiph = argSENSORfastcgiph;
		sensorfastcgitb = argSENSORfastcgitb;
		sensorfastcgitp = argSENSORfastcgitp;
	}

	/**
	 * Gets the data sends it to the webserver -> client.
	 **/
	virtual std::string getJSONString() {
		drinkable(sensorfastcgivm, sensorfastcgiph, sensorfastcgitb, sensorfastcgitp);
		JSONCGIHandler::JSONGenerator jsonGenerator;
		jsonGenerator.add("epoch",(long)time(NULL));
		jsonGenerator.add("volumeValues",sensorfastcgivm->getData());
		jsonGenerator.add("waterDetected",sensorfastcgivm->waterDetected());
		jsonGenerator.add("phValues",sensorfastcgiph->getData());
		jsonGenerator.add("phType",sensorfastcgiph->getType());
		jsonGenerator.add("turbidityValues",sensorfastcgitb->getData());
		jsonGenerator.add("turbidityType",sensorfastcgitb->getType());
		jsonGenerator.add("temperatureValues",sensorfastcgitp->getData());
		jsonGenerator.add("temperatureType",sensorfastcgitp->getType());
		jsonGenerator.add("drinkable",drinkable(sensorfastcgivm, sensorfastcgiph, sensorfastcgitb, sensorfastcgitp));
		jsonGenerator.add("fs",(float)(sensorfastcgiph->getADS1115settings().getSamplingRate()));
		return jsonGenerator.getJSON();
	}
};

/**
 * Callback handler which receives the JSON from jQuery
 **/
class SENSORPOSTCallback : public JSONCGIHandler::POSTCallback {
public:
	SENSORPOSTCallback(ADS1115PrinterVM* argSENSORfastcgivm, ADS1115PrinterPH* argSENSORfastcgiph, 
	ADS1115PrinterTB* argSENSORfastcgitb, ADS1115PrinterTP* argSENSORfastcgitp) {
		sensorfastcgivm = argSENSORfastcgivm;
		sensorfastcgiph = argSENSORfastcgiph;
		sensorfastcgitb = argSENSORfastcgitb;
		sensorfastcgitp = argSENSORfastcgitp;
	}

	/**
	 * We force the voltage readings in the buffer to
	 * a certain value.
	 **/
	virtual void postString(std::string postArg) {
		auto m = JSONCGIHandler::postDecoder(postArg);
		float temp = atof(m["volt"].c_str());
		std::cerr << m["hello"] << "\n";
		sensorfastcgiph->forceValue(temp);
	}

	/**
	 * Pointer to the handler which keeps the adc values
	 **/
	ADS1115PrinterVM* sensorfastcgivm;
	ADS1115PrinterPH* sensorfastcgiph;
	ADS1115PrinterTB* sensorfastcgitb;
	ADS1115PrinterTP* sensorfastcgitp;
};



int main(int argc, char *argv[]) {

	ADS1115PrinterVM sensorcommvm;
	ADS1115PrinterPH sensorcommph;
	ADS1115PrinterTB sensorcommtb;
	ADS1115PrinterTP sensorcommtp;
	JSONCGIADCCallback fastCGIADCCallback(&sensorcommvm, &sensorcommph, &sensorcommtb, &sensorcommtp);
	SENSORPOSTCallback postCallback(&sensorcommvm, &sensorcommph, &sensorcommtb, &sensorcommtp);
	
	JSONCGIHandler* fastCGIHandler = new JSONCGIHandler(&fastCGIADCCallback,
							    &postCallback,
							    "/tmp/sensorsocket");
	setHUPHandler();

	fprintf(stderr,"'%s' up and running.\n",argv[0]);

	sensorcommvm.startThread();
	sensorcommph.startThread();
	sensorcommtb.startThread();
	sensorcommtp.startThread();
	
	fprintf(stderr,"'%s' finished running. You can exit\n",argv[0]);
	while (mainRunning) sleep(1);
		
	// stops the fast CGI handlder
	delete fastCGIHandler;
	//exit(1);
	
	return 0;
}
