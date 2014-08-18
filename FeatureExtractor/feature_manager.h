//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_MANAGER_H_
#define FEATURE_MANAGER_H_

#include <opencv2/core/core.hpp>
#include <NiTE.h>
#include <vector>

class FeatureManager
{
public:
	FeatureManager();
	~FeatureManager();
	void ReceiveONIReader_n_Process(std::vector<cv::Mat> depth_frames, std::vector<nite::Skeleton> skeletons, std::vector<bool> user_tracked, const int frame_no);

	int frame_no_;
	std::vector<double> feature_contraction_;
	std::vector<double> feature_stability_;
	std::vector<double> feature_energy_;
	std::vector<double> feature_direction_;
	std::vector<double> feature_impulse_;
	std::vector<double> feature_displacement_;

protected:
private:
	std::vector<double> energy_buffer_4_impulse_;
};

#endif