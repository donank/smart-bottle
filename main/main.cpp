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
	std::deque<float> volumeValues;
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		
		volumeValues.push_back(v);
		
		if (volumeValues.size() > maxBufSize) volumeValues.pop_front();
	}
	
	void forceValue(float a) {
		
		for(auto& v:volumeValues) {
			v = a;
		}
	}
};

class ADS1115PrinterPH : public ph {
public:
	std::deque<float> phValues;
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		
		phValues.push_back(v);
		
		if (phValues.size() > maxBufSize) phValues.pop_front();
	}
	
	void forceValue(float a) {
		
		for(auto& v:phValues) {
			v = a;
		}
	}
};

class ADS1115PrinterTB : public turbidity {
public:
	std::deque<float> turbidityValues;
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		
		turbidityValues.push_back(v);
		
		if (turbidityValues.size() > maxBufSize) turbidityValues.pop_front();
	}
	
	void forceValue(float a) {
		
		for(auto& v:turbidityValues) {
			v = a;
		}
	}
};

class ADS1115PrinterTP : public temperature {
public:
	std::deque<float> temperatureValues;
	const int maxBufSize = 50; 

	virtual void hasSample(float v){
		
		temperatureValues.push_back(v);
		
		if (temperatureValues.size() > maxBufSize) temperatureValues.pop_front();
	}
	
	void forceValue(float a) {
		
		for(auto& v:temperatureValues) {
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
		JSONCGIHandler::JSONGenerator jsonGenerator;
		jsonGenerator.add("epoch",(long)time(NULL));
		jsonGenerator.add("volumeValues",sensorfastcgivm->volumeValues);
		jsonGenerator.add("phValues",sensorfastcgiph->phValues);
		jsonGenerator.add("turbidityValues",sensorfastcgitb->turbidityValues);
		jsonGenerator.add("temperatureValues",sensorfastcgitp->temperatureValues);
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

	sensorcommvm.startThread();
	sensorcommph.startThread();
	sensorcommtb.startThread();
	sensorcommtp.startThread();
	setHUPHandler();

    fprintf(stderr,"'%s' up and running.\n",argv[0]);
	
	while (mainRunning) sleep(1);
		
	// stops the fast CGI handlder
	delete fastCGIHandler;

	
	return 0;
}
