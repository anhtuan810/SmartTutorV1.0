//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.18
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_DISPLACEMENT_H_
#define FEATURE_DISPLACEMENT_H_

#include "sample.h"
#include <opencv2/core/core.hpp>
#include <vector>

class FeatureDisplacement
{
public:
	FeatureDisplacement();
	~FeatureDisplacement();
	double GetDisplacement(Sample &sample);

protected:
private:
	cv::Point3f FeatureDisplacement::GetCentroid(Sample &sample);
	double FeatureDisplacement::GetDistance(cv::Point3f &p1, cv::Point3f &p2);
	std::vector<Sample> buff_samples_;
};


#endif