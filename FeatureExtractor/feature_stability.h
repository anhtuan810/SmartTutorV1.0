//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_STABILITY_H_
#define FEATURE_STABILITY_H_

#include "sample.h"
#include "opencv2/core/core.hpp"

class FeatureStability
{
public:
	FeatureStability();
	~FeatureStability();
	double GetStability(Sample &sample);

protected:
private:
	cv::Mat GetProjectedFrame(Sample &sample);
	cv::Point GetWeightCenter(cv::Mat &ground_projected);
	cv::Rect GetFootBoundingBox(Sample &sample, cv::Mat &ground_projected);
};

#endif