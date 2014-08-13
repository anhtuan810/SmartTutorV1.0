//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef GRABBER_KINECT_H_
#define GRABBER_KINECT_H_

#include <OpenNI.h>
#include "grabber.h"


class GrabberKinect : public Grabber
{
public:
	openni::VideoStream color_stream_;
	openni::VideoStream depth_stream_;

	GrabberKinect();
	~GrabberKinect();
	bool InitiateOrDie();
	bool TurnOn();
	void TurnOff();

protected:

private:
	openni::Device device_;
	openni::Status status_openni_;
};


#endif