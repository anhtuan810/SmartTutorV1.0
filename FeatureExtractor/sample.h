//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <opencv2/core/core.hpp>
#include <NiTE.h>

class Sample
{
public:
	Sample();
	~Sample();
	Sample(cv::Mat &depth_image_, nite::Skeleton &skeletons);

	nite::Skeleton skeleton_;
	cv::Mat depth_;
	cv::Mat depth_upper_;
	cv::Mat depth_lower_;
	cv::Mat depth_upper_shifted_;
	cv::Mat depth_lower_shifted_;
	cv::Mat proj_X_, proj_Y_, proj_Z_;
	cv::Mat proj_upper_shifted_X_, proj_upper_shifted_Y_, proj_upper_shifted_Z_;
	cv::Mat proj_lower_shifted_X_, proj_lower_shifted_Y_, proj_lower_shifted_Z_;

protected:
private:
	void RemoveDepthNoise(cv::Mat &input);
	cv::Mat GetUpperBody(cv::Mat &input);
	cv::Mat GetLowerBody(cv::Mat &input);
	cv::Mat CenterImg(cv::Mat &input);
	std::vector<cv::Mat> Project(cv::Mat &input);
	cv::Mat Dilation(cv::Mat &input);
};

#endif