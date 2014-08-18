//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08..18
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_DIRECTION_H_
#define FEATURE_DIRECTION_H_

#include "sample.h"
#include "opencv2/core/core.hpp"
#include <vector>

class FeatureDirection
{
public:
	FeatureDirection();
	~FeatureDirection();
	double GetDirection(Sample &sample);
protected:
private:
	std::vector<Sample> buff_sample;
	cv::Point GetCentralMat(cv::Mat &input);
};

#endif