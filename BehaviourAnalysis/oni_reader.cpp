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

void ONIReader::ReadONI(char* file_name)
{
	file_name_ = file_name;

	openni::OpenNI::initialize();
	nite::NiTE::initialize();

	Device device;
	device.open(file_name);
	PlaybackControl *playback = device.getPlaybackControl();
	VideoStream depth_stream;
	UserTracker user_tracker;
	depth_stream.create(device, SENSOR_DEPTH);
	user_tracker.create(&device);
	depth_stream.start();

	frame_number_ = playback->getNumberOfFrames(depth_stream);
	skeletons_ = new Skeleton[frame_number_];
	depth_user_frames_ = new Mat[frame_number_];
	const int kHeight = 480;
	const int kWidth = 640;

	for (size_t i = 0; i < frame_number_; i++)
	{
		cout << i << "\n";
		user_tracked_[i] = false;

		playback->seek(depth_stream, i);
		VideoFrameRef depth_frame;
		UserTrackerFrameRef user_frame;
		depth_stream.readFrame(&depth_frame);
		user_tracker.readFrame(&user_frame);


		// Check if contain at least one user
		depth_user_frames_[i] = cv::Mat(kHeight, kWidth, CV_16U);
		if (user_frame.getUsers().getSize() == 0)
			continue;


		// Initiate skeleton tracker
		UserData user_data = user_frame.getUsers()[0];
		user_tracker.startSkeletonTracking(user_data.getId());
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
	depth_stream.stop();
}