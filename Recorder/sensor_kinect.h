//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "sensor.h"
#include "OpenNI.h"

class SensorKinect : public Sensor
{
public:
	SensorKinect();
	~SensorKinect();
	bool TurnOnOrDie();
	void TurnOff();
	bool StartRecordingOrDie(const char* file_name);
	void StopRecording();
	char* GrabFrame();

protected:
private:
	openni::Status status_openni_;
	openni::Device device_;
	openni::VideoStream depth_stream_;
	openni::VideoStream color_stream_;
	openni::Recorder recorder_;
};