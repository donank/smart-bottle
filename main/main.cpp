#include <iostream>
#include "ads1115rpi.h"
#include <chrono>
#include "ph.h"
#include "turbidity.h"
#include<thread>
#include<unistd.h>
#include "json_fastcgi_web_api.h"
#include <string.h>

ph ph;
turbidity tb;

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
class ADS1115Printer : public ADS1115rpi {
public:
	std::deque<float> volumeValues;
	std::deque<float> phValues;
	std::deque<float> turbidityValues;
	std::deque<float> temperatureValues;

	const int maxBufSize = 50; 
	std::string sensorType;

	virtual void hasSample(float v){
		
		if(sensorType == "volume"){
			volumeValues.push_back(v);
		}else if(sensorType == "ph"){
			phValues.push_back(v);
		}else if(sensorType == "turbidity"){
			turbidityValues.push_back(v);
		}else if(sensorType == "temperature"){
			temperatureValues.push_back(v);
		}
		if (volumeValues.size() > maxBufSize) volumeValues.pop_front();
		if (phValues.size() > maxBufSize) phValues.pop_front();
		if (turbidityValues.size() > maxBufSize) turbidityValues.pop_front();
		if (temperatureValues.size() > maxBufSize) temperatureValues.pop_front();
	}
	
	void forceValue(float a) {
		
		for(auto& v:volumeValues) {
			v = a;
		}
	}

	void setSensor(std::string str){
		sensorType = str;
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
	ADS1115Printer* sensorfastcgi;

public:
	/**
	 * Constructor: argument is the ADC callback handler
	 * which keeps the data as a simple example.
	 **/
	JSONCGIADCCallback(ADS1115Printer* argSENSORfastcgi) {
		sensorfastcgi = argSENSORfastcgi;
	}

	/**
	 * Gets the data sends it to the webserver -> client.
	 **/
	virtual std::string getJSONString() {
		JSONCGIHandler::JSONGenerator jsonGenerator;
		jsonGenerator.add("epoch",(long)time(NULL));
		//jsonGenerator.add("type",sensorfastcgi->sensorType);
		jsonGenerator.add("volumeValues",sensorfastcgi->volumeValues);
		jsonGenerator.add("phValues",sensorfastcgi->phValues);
		jsonGenerator.add("turbidityValues",sensorfastcgi->turbidityValues);
		jsonGenerator.add("temperatureValues",sensorfastcgi->temperatureValues);
		jsonGenerator.add("fs",(float)(sensorfastcgi->getADS1115settings().getSamplingRate()));
		return jsonGenerator.getJSON();
	}
};

/**
 * Callback handler which receives the JSON from jQuery
 **/
class SENSORPOSTCallback : public JSONCGIHandler::POSTCallback {
public:
	SENSORPOSTCallback(ADS1115Printer* argSENSORfastcgi) {
		sensorfastcgi = argSENSORfastcgi;
	}

	/**
	 * We force the voltage readings in the buffer to
	 * a certain value.
	 **/
	virtual void postString(std::string postArg) {
		auto m = JSONCGIHandler::postDecoder(postArg);
		float temp = atof(m["volt"].c_str());
		std::cerr << m["hello"] << "\n";
		sensorfastcgi->forceValue(temp);
	}

	/**
	 * Pointer to the handler which keeps the adc values
	 **/
	ADS1115Printer* sensorfastcgi;
};


int main(int argc, char *argv[]) {
	ADS1115Printer sensorcomm;
	JSONCGIADCCallback fastCGIADCCallback(&sensorcomm);
	SENSORPOSTCallback postCallback(&sensorcomm);
	
	JSONCGIHandler* fastCGIHandler = new JSONCGIHandler(&fastCGIADCCallback,
							    &postCallback,
							    "/tmp/sensorsocket");

	setHUPHandler();

    fprintf(stderr,"'%s' up and running.\n",argv[0]);
    ADS1115settings s;
	s.samplingRate = ADS1115settings::FS8HZ;
	using std::chrono::system_clock;
    std::time_t start_time = system_clock::to_time_t (system_clock::now());
    int flag1 = 1;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;

	while(flag1){
        s.channel = s.AIN0;
		sensorcomm.setSensor("volume");
		sensorcomm.start(s);

        std::time_t curr_time = system_clock::to_time_t (system_clock::now());
        if(curr_time - start_time == 5){
                flag1 = 0;
				flag2 = 1;
                printf("volume check finished \n");
                sensorcomm.stop();
        } 

    }

	while(flag2){
        s.channel = s.AIN1;
		sensorcomm.setSensor("ph");
		sensorcomm.start(s);
		
        std::time_t curr_time = system_clock::to_time_t (system_clock::now());
        if(curr_time - start_time == 10){
                flag2 = 0;
				flag3 = 1;
                printf("ph check finished \n");
                sensorcomm.stop();
        } 

    }

	while(flag3){
        s.channel = s.AIN2;
		sensorcomm.setSensor("turbidity");
		sensorcomm.start(s);

        std::time_t curr_time = system_clock::to_time_t (system_clock::now());
        if(curr_time - start_time == 15){
                flag3 = 0;
				flag4 = 1;
                printf("turbidity check finished\n");
                sensorcomm.stop();
        } 

    }

	while(flag4){
        s.channel = s.AIN3;
		sensorcomm.setSensor("temperature");
		sensorcomm.start(s);

        std::time_t curr_time = system_clock::to_time_t (system_clock::now());
        if(curr_time - start_time == 20){
                flag4 = 0;
				flag1 = 1;
                printf("temperature check finished \n");
                sensorcomm.stop();

        } 

    }
	
	while (mainRunning) sleep(1);
		
	// stops the fast CGI handlder
	delete fastCGIHandler;

	
	return 0;
}
