//
//  Smart Tutor v1.0
//	Behaviour Analysis
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "oni_reader.h"
#include <iostream>

using namespace openni;
using namespace nite;
using namespace std;
using namespace cv;

ONIReader::ONIReader(){}

ONIReader::~ONIReader(){}

bool ONIReader::InitiateOrDie()
{
	openni::Status openni_status = OpenNI::initialize();
	nite::Status nite_status = NiTE::initialize();

	openni_status = device_.open(file_name_);
	if (openni_status != openni::STATUS_OK)
		return false;

	playback_ = device_.getPlaybackControl();
	openni_status = depth_stream_.create(device_, SENSOR_DEPTH);
	if (openni_status != openni::STATUS_OK)
		return false;

	nite_status = user_tracker_.create(&device_);
	if (nite_status != nite::STATUS_OK)
		return false;

	openni_status = depth_stream_.start();
	if (openni_status != openni::STATUS_OK)
		return false;

	frame_number_ = playback_->getNumberOfFrames(depth_stream_);
	user_tracked_ = new bool[frame_number_];
	skeletons_ = new Skeleton[frame_number_];
	depth_user_frames_ = new Mat[frame_number_];

	return true;
}


bool ONIReader::ReadONI(char* file_name)
{
	file_name_ = file_name;
	bool init_result = InitiateOrDie();
	if (init_result == false)
		return false;

	const int kHeight = 480;
	const int kWidth = 640;

	for (size_t i = 0; i < frame_number_; i++)
	{
		cout << i << "\n";
		user_tracked_[i] = false;

		playback_->seek(depth_stream_, i);
		VideoFrameRef depth_frame;
		UserTrackerFrameRef user_frame;
		depth_stream_.readFrame(&depth_frame);
		user_tracker_.readFrame(&user_frame);


		// Check if contain at least one user
		depth_user_frames_[i] = cv::Mat(kHeight, kWidth, CV_16U);
		if (user_frame.getUsers().getSize() == 0)
			continue;


		// Initiate skeleton tracker
		UserData user_data = user_frame.getUsers()[0];
		user_tracker_.startSkeletonTracking(user_data.getId());
		Skeleton skeleton = user_data.getSkeleton();
		if (skeleton.getState() != SkeletonState::SKELETON_TRACKED)
			continue;


		// Draw depth map
		cv::Mat depth_cvmat(kHeight, kWidth, CV_16U);
		const DepthPixel* pt = (const DepthPixel*)depth_frame.getData();
		std::memcpy(depth_cvmat.data, pt, kHeight * kWidth * 2);
		

		// Draw depth user map
		cv::Mat depth_user_cvmat(kHeight, kWidth, CV_16U);
		depth_user_cvmat = cv::Scalar(0);
		//std::memcpy(depth_user_cvmat.data, depth_cvmat.data, kHeight * kWidth * 2);
		const UserMap& user_map = user_frame.getUserMap();
		const UserId* label = user_map.getPixels();
		for (int j = 0; j < kHeight * kWidth * 2; j++)
		{
			if (label[j / 2] != 0)
				depth_user_cvmat.data[j] = depth_cvmat.data[j];
		}

		// Write data
		user_tracked_[i] = true;
		depth_user_frames_[i] = depth_user_cvmat;
		skeletons_[i] = skeleton;
	}

	depth_stream_.stop();
	return true;
}