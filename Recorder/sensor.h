//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef SENSOR_H_
#define SENSOR_H_

enum SensorState
{
	TURNED_OFF,
	TURNED_ON,
	RECORDING,
};


class Sensor
{
public:
	Sensor();
	~Sensor();
	SensorState GetSensorState();
	virtual bool TurnOnOrDie() = 0;
	virtual void TurnOff() = 0;
	virtual bool StartRecordingOrDie(const char* file_name) = 0;
	virtual void StopRecording() = 0;
	virtual char* GrabFrame() = 0;
	
protected:
	SensorState sensor_state_;
private:
};

#endif