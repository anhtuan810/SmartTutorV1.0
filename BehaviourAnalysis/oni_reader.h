//
//  Smart Tutor v1.0
//	Behaviour Analysis
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef ONI_READER_H_
#define ONI_READER_H_

#include <list>
#include <OpenNI.h>
#include <NiTE.h>
#include <opencv2\core\core.hpp>

class ONIReader
{
public:
	ONIReader();
	~ONIReader();
	bool ReadONI(char* file_name);

	int frame_number_;
	bool* user_tracked_;
	nite::Skeleton* skeletons_;
	cv::Mat* depth_user_frames_;
protected:
private:
	bool InitiateOrDie();

	char* file_name_;
	openni::Device device_;
	openni::PlaybackControl *playback_;
	openni::VideoStream depth_stream_;
	nite::UserTracker user_tracker_;
};


#endif