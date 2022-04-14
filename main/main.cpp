#include <iostream>
#include "ads1115rpi.h"
#include <chrono>
#include "ph.h"
#include "turbidity.h"
#include<thread>
#include<unistd.h>
#include "json_fastcgi_web_api.h"
#include <string.h>

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
	ADS1115PrinterPH* sensorfastcgiph;
	ADS1115PrinterTB* sensorfastcgitb;

public:
	/**
	 * Constructor: argument is the ADC callback handler
	 * which keeps the data as a simple example.
	 **/
	JSONCGIADCCallback(ADS1115PrinterPH* argSENSORfastcgiph, ADS1115PrinterTB* argSENSORfastcgitb) {
		sensorfastcgiph = argSENSORfastcgiph;
		sensorfastcgitb = argSENSORfastcgitb;
	}

	/**
	 * Gets the data sends it to the webserver -> client.
	 **/
	virtual std::string getJSONString() {
		JSONCGIHandler::JSONGenerator jsonGenerator;
		jsonGenerator.add("epoch",(long)time(NULL));
		jsonGenerator.add("volumeValues",sensorfastcgiph->phValues);
		jsonGenerator.add("phValues",sensorfastcgiph->phValues);
		jsonGenerator.add("turbidityValues",sensorfastcgitb->turbidityValues);
		jsonGenerator.add("temperatureValues",sensorfastcgitb->turbidityValues);
		jsonGenerator.add("fs",(float)(sensorfastcgiph->getADS1115settings().getSamplingRate()));
		return jsonGenerator.getJSON();
	}
};

/**
 * Callback handler which receives the JSON from jQuery
 **/
class SENSORPOSTCallback : public JSONCGIHandler::POSTCallback {
public:
	SENSORPOSTCallback(ADS1115PrinterPH* argSENSORfastcgiph, ADS1115PrinterTB* argSENSORfastcgitb) {
		sensorfastcgiph = argSENSORfastcgiph;
		sensorfastcgitb = argSENSORfastcgitb;
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
	ADS1115PrinterPH* sensorfastcgiph;
	ADS1115PrinterTB* sensorfastcgitb;
};


int main(int argc, char *argv[]) {

	ADS1115PrinterPH sensorcommph;
	ADS1115PrinterTB sensorcommtb;
	JSONCGIADCCallback fastCGIADCCallback(&sensorcommph, &sensorcommtb);
	SENSORPOSTCallback postCallback(&sensorcommph, &sensorcommtb);
	
	JSONCGIHandler* fastCGIHandler = new JSONCGIHandler(&fastCGIADCCallback,
							    &postCallback,
							    "/tmp/sensorsocket");

	sensorcommph.startThread();
	sensorcommtb.startThread();
	setHUPHandler();

    fprintf(stderr,"'%s' up and running.\n",argv[0]);
	
	while (mainRunning) sleep(1);
		
	// stops the fast CGI handlder
	delete fastCGIHandler;

	
	return 0;
}
