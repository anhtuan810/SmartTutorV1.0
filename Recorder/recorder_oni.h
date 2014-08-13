//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "recorder.h"
#include "grabber_kinect.h"

class RecorderONI : public Recorder
{
public:
	RecorderONI();
	~RecorderONI();
	bool InitiateOrDie();
	bool StartRecording();
	void StopRecording();

protected:
private:
	GrabberKinect grab_kinect_;
	openni::Recorder recorder_;
};

