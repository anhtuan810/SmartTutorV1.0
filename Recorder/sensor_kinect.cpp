//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "sensor_kinect.h"
#include <OpenNI.h>
#include <iostream>

using namespace openni;


SensorKinect::SensorKinect()
{
	sensor_state_ = SensorState::TURNED_OFF;
}

SensorKinect::~SensorKinect()
{
	depth_stream_.destroy();
	color_stream_.destroy();
	if (recorder_.isValid()) 
		recorder_.destroy();
}


bool SensorKinect::TurnOnOrDie()
{
	status_openni_ = OpenNI::initialize();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = device_.open(openni::ANY_DEVICE);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	depth_stream_.create(device_, SENSOR_DEPTH);
	status_openni_ = depth_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	color_stream_.create(device_, SENSOR_COLOR);
	status_openni_ = color_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	sensor_state_ = SensorState::TURNED_ON;
	return true;
}


char* SensorKinect::GrabFrame()
{
	openni::VideoFrameRef frame;
	color_stream_.readFrame(&frame);

	char* color_data;
	color_data = new char[640 * 480 * 3];
	std::memcpy(color_data, frame.getData(), 640 * 480 * 3);

	return color_data;
}


bool SensorKinect::StartRecordingOrDie(const char *file_name)
{
	recorder_.create(file_name);
	recorder_.attach(color_stream_);
	recorder_.attach(depth_stream_);

	if (recorder_.start() != ONI_STATUS_OK)
		return false;
	else
	{
		sensor_state_ = SensorState::RECORDING;
		return true;
	}
}


void SensorKinect::StopRecording()
{
	recorder_.stop();
	recorder_.destroy();
	sensor_state_ = SensorState::TURNED_ON;
}


void SensorKinect::TurnOff()
{
	depth_stream_.stop();
	depth_stream_.destroy();
	color_stream_.stop();
	color_stream_.destroy();
	device_.close();
	sensor_state_ = SensorState::TURNED_OFF;
}