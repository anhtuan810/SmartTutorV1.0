//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.18
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_displacement.h"


FeatureDisplacement::FeatureDisplacement(){}
FeatureDisplacement::~FeatureDisplacement(){}



//************************************
// Method:    GetDisplacement
// FullName:  FeatureDisplacement::GetDisplacement
// Access:    public 
// Returns:   double
// Qualifier:
// Parameter: Sample & sample
//************************************
double FeatureDisplacement::GetDisplacement(Sample &sample)
{
	const int kBuffSize = 10;
	buff_samples_.push_back(sample);
	if (buff_samples_.size() > kBuffSize)
		buff_samples_.erase(buff_samples_.begin());

	double disp = 0;
	if (buff_samples_.size() >= 2)
	{
		for (size_t i = buff_samples_.size() - 1; i >= 1; i--)
		{
			cv::Point3f c1 = GetCentroid(buff_samples_[i]);
			cv::Point3f c2 = GetCentroid(buff_samples_[i - 1]);
			disp += GetDistance(c1, c2);
		}
	}
	return disp;
}



//************************************
// Method:    GetCentroid
// FullName:  FeatureDisplacement::GetCentroid
// Access:    private 
// Returns:   cv::Point3f
// Qualifier:
// Parameter: Sample & sample
//************************************
cv::Point3f FeatureDisplacement::GetCentroid(Sample &sample)
{
	cv::Point3f ptOut(0, 0, 0);
	cv::Mat matDepth = sample.depth_;
	int iCount = 0;
	for (size_t r = 0; r < matDepth.rows; r++)
	{
		for (size_t c = 0; c < matDepth.cols; c++)
		{
			uint16_t depth = matDepth.at<uint16_t>(r, c);
			if (depth > 0)
			{
				ptOut.x += (float)c;
				ptOut.y += (float)r;
				ptOut.z += (float)depth / 100;
				iCount++;
			}
		}
	}
	if (iCount > 0)
	{
		ptOut.x = ptOut.x / iCount;
		ptOut.y = ptOut.y / iCount;
		ptOut.z = ptOut.z / iCount;
	}
	return ptOut;
}



//************************************
// Method:    GetDistance
// FullName:  FeatureDisplacement::GetDistance
// Access:    private 
// Returns:   double
// Qualifier:
// Parameter: cv::Point3f & p1
// Parameter: cv::Point3f & p2
//************************************
double FeatureDisplacement::GetDistance(cv::Point3f &p1, cv::Point3f &p2)
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
		(p1.y - p2.y) * (p1.y - p2.y) +
		(p1.z - p2.z) * (p1.z - p2.z));
}
