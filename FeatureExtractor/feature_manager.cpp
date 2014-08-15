//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_manager.h"
#include "sample.h"
#include "feature_contraction.h"
#include "feature_stability.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

FeatureManager::FeatureManager(){}
FeatureManager::~FeatureManager(){}

void FeatureManager::ReceiveONIReader_n_Process(
	std::vector<cv::Mat> depth_frames,
	std::vector<nite::Skeleton> skeletons,
	std::vector<bool> user_tracked,
	const int frame_no)
{
	frame_no_ = frame_no;
	FeatureContraction contraction_extractor;
	FeatureStability stability_extractor;

	for (size_t i = 0; i < frame_no; i++)
	{
		double contraction = 0,
			stability = 0;

		if (user_tracked[i])
		{
			std::cout << i << "tracked \n";
			cv::Mat frm = depth_frames[i];
			nite::Skeleton skel = skeletons[i];

			Sample sample(frm, skel);
			contraction = contraction_extractor.GetContraction(sample);	
			stability = stability_extractor.GetStability(sample);
		}
		feature_contraction_.push_back(contraction);
		feature_stability_.push_back(stability);
	}
}
