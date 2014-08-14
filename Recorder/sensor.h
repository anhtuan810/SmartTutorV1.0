//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#ifndef SENSOR_H_
#define SENSOR_H_


class Sensor
{
public:
	Sensor();
	~Sensor();
	virtual bool TurnOnOrDie() = 0;
	virtual void TurnOff() = 0;
	virtual bool StartRecordingOrDie(const char* file_name) = 0;
	virtual void StopRecording() = 0;
	virtual char* GrabFrame() = 0;
	
protected:
private:
};

#endif