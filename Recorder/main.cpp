#include "recorder_oni.h";
#include "grabber_kinect.h"


void main()
{
	RecorderONI recorder_oni;
	recorder_oni.InitiateOrDie();
	recorder_oni.SetFileName("C:\\1.oni");
	recorder_oni.StartRecording();
	Sleep(2000);
	recorder_oni.StopRecording();

	//GrabberKinect grab_kinect;
	//bool init_result = grab_kinect.InitiateOrDie();
	//if (init_result == false)
	//	return;

	//bool turn_on_result = grab_kinect.TurnOn();
	//if (turn_on_result == false)
	//	return;

	//openni::Recorder recorder;
	//recorder.create("C:\\test.oni");
	//recorder.attach(grab_kinect.color_stream_);
	//recorder.attach(grab_kinect.depth_stream_);
	//recorder.start();

	//Sleep(2000);

	//recorder.stop();
	//recorder.destroy();

	//grab_kinect.TurnOff();

	return;
}