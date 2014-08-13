//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include <OpenNI.h>
#include <NiTE.h>
#include "grabber_kinect.h"

using namespace openni;
using namespace std;

GrabberKinect::GrabberKinect(){}

GrabberKinect::~GrabberKinect(){}


bool GrabberKinect::InitiateOrDie()
{
	status_openni_ = OpenNI::initialize();

	status_openni_ = device_.open(openni::ANY_DEVICE);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	return true;
}


bool GrabberKinect::TurnOn()
{
	depth_stream_.create(device_, SENSOR_DEPTH);
	status_openni_ = depth_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	color_stream_.create(device_, SENSOR_COLOR);
	status_openni_ = color_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	return true;
}


void GrabberKinect::TurnOff()
{
	depth_stream_.stop();
	depth_stream_.destroy();
	color_stream_.stop();
	color_stream_.destroy();
	device_.close();
}
