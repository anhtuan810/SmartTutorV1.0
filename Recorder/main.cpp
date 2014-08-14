//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "sensor_kinect.h"

void main()
{
	
	SensorKinect sensor;
	sensor.TurnOnOrDie();
	sensor.StartRecordingOrDie("C:\\2.oni");
	Sleep(2000);
	sensor.StopRecording();
	sensor.TurnOff();

	return;
}