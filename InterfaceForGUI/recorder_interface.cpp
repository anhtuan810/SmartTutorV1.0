#include "recorder_interface.h"
#include "sensor_kinect.h"


SensorKinect sensor_;

void StartRecordingONI(char* file_name)
{
	sensor_.StartRecordingOrDie(file_name);
}

void StopRecordingONI()
{
	sensor_.StopRecording();
}

void TurnOnKinectSensor()
{
	sensor_.TurnOnOrDie();
}

void TurnOffKinectSensor()
{
	sensor_.TurnOff();
}

char* GrabFrame()
{
	return sensor_.GrabFrame();
}