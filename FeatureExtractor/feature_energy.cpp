//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_energy.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "img_processing_functions.h"

FeatureEnergy::FeatureEnergy(){}
FeatureEnergy::~FeatureEnergy(){}


//************************************
// Method:    GetEnergy
// FullName:  FeatureEnergy::GetEnergy
// Access:    public 
// Returns:   double
// Qualifier:
//************************************
double FeatureEnergy::GetEnergy(Sample &sample)
{
	const int kBuffSize = 10;
	buffer_.push_back(sample);
	if (buffer_.size() > kBuffSize)
		buffer_.erase(buffer_.begin());
	
	double energy = 0;
	if (buffer_.size() >= 2)
	{
		std::vector<cv::Mat> proj_X, proj_Y, proj_Z;
		for (size_t i = 0; i < buffer_.size(); i++)
		{
			proj_X.push_back(buffer_[i].proj_X_);
			proj_Y.push_back(buffer_[i].proj_Y_);
			proj_Z.push_back(buffer_[i].proj_Z_);
		}

		cv::Mat MEI_X = ImgProcessingFunctions::MEI_int16(proj_X);
		cv::Mat MEI_Y = ImgProcessingFunctions::MEI_int16(proj_Y);
		cv::Mat MEI_Z = ImgProcessingFunctions::MEI_int16(proj_Z);

		double count_X = cv::countNonZero(MEI_X);
		double count_Y = cv::countNonZero(MEI_Y);
		double count_Z = cv::countNonZero(MEI_Z);

		energy = std::sqrt(count_X * count_X + count_Y * count_Y + count_Z * count_Z);
	}

	return energy;
}