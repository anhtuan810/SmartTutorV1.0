//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.18
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_direction.h"
#include "img_processing_functions.h"
#include <opencv2/highgui/highgui.hpp>

FeatureDirection::FeatureDirection(){};
FeatureDirection::~FeatureDirection(){};


//************************************
// Method:    GetDirection
// Compute direction index based on the created MHI
// -- Remove the latest silhouette
// -- Divide into 2 areas based on current silhouette
// -- Compute direction index
// FullName:  FeatureDirection::GetDirection
// Access:    public 
// Returns:   double
// Qualifier:
// Parameter: Sample & Sample
//************************************
double FeatureDirection::GetDirection(Sample &sample)
{
	//----------------------------------------------------------
	// Push new sample to buffer
	int kBuffSize = 10;
	buff_sample.push_back(sample);
	if (buff_sample.size() > kBuffSize)
		buff_sample.erase(buff_sample.begin());

	//----------------------------------------------------------
	// Convert the buffer to the X-projections
	double direction = 0;
	std::vector<cv::Mat> buff_proj_X;
	for (size_t i = 0; i < buff_sample.size(); i++)
	{
		buff_proj_X.push_back(buff_sample[i].proj_X_);
	}

	//----------------------------------------------------------
	// Compute direction if > 2 samples in buffer
	if (buff_sample.size() >= 2)
	{
		cv::Mat MEI_X = ImgProcessingFunctions::MEI_int16(buff_proj_X);

		// Process MEI to get the direction index
		int area_left = 0;
		int area_right = 0;
		int height = MEI_X.size().height;
		int width = MEI_X.size().width;
		cv::Point central_point = GetCentralMat(buff_proj_X[buff_proj_X.size() - 1]);
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				int px = MEI_X.at<__int16>(h, w);
				if (px != 0)
				{
					if (w < central_point.x)
						area_left += px;
					else
						area_right += px;
				}
			}
		}

		// Create index based on size of 2 regions
		int area_user_region = cv::countNonZero(buff_proj_X[buff_proj_X.size() - 1]);
		if (area_user_region > 0)
		{
			direction = (double)(area_right - area_left) / area_user_region;
		}
	}
	return direction;
}


//************************************
// Method:    GetCentralMat
// FullName:  FeatureDirection::GetCentralMat
// Access:    private 
// Returns:   cv::Point
// Qualifier:
// Parameter: cv::Mat & input
//************************************
cv::Point FeatureDirection::GetCentralMat(cv::Mat &input)
{
	int height = input.size().height;
	int width = input.size().width;
	double sumH = 0;
	double sumW = 0;
	int count = 0;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			__int16 value = input.at<__int16>(h, w);
			if (value != 0)
			{
				sumH += h;
				sumW += w;
				count++;
			}
		}
	}
	return cv::Point(sumW / count, sumH / count);
}

