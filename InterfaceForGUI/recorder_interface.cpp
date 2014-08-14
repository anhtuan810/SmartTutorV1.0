//
//  Smart Tutor v1.0
//	InterfaceForGUI
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "recorder_interface.h"
#include "sensor_kinect.h"


SensorKinect sensor_;

bool IStartRecordingONI(char* file_name)
{
	return sensor_.StartRecordingOrDie(file_name);
}

void IStopRecordingONI()
{
	sensor_.StopRecording();
}

bool ITurnOnKinectSensor()
{
	return sensor_.TurnOnOrDie();
}

void ITurnOffKinectSensor()
{
	sensor_.TurnOff();
}

char* IGrabFrame()
{
	return sensor_.GrabFrame();
}