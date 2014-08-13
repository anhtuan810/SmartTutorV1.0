//
//  Smart Tutor v1.0
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "recorder_oni.h"
#include "OpenNI.h"

RecorderONI::RecorderONI(){}

RecorderONI::~RecorderONI(){}

bool RecorderONI::InitiateOrDie()
{
	bool result = grab_kinect_.InitiateOrDie();
	if (!result) return false;

	result = grab_kinect_.TurnOn();
	if (!result) return false;

	return true;
}

bool RecorderONI::StartRecording()
{
	if (file_name_ == 0) 
		return false;

	recorder_.create(file_name_);
	recorder_.attach(grab_kinect_.color_stream_);
	recorder_.attach(grab_kinect_.depth_stream_);

	if (recorder_.start() != ONI_STATUS_OK) 
		return false;

	return true;
}

void RecorderONI::StopRecording()
{
	recorder_.stop();
	recorder_.destroy();
	grab_kinect_.TurnOff();
}
