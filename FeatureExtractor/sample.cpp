//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "sample.h"
#include "img_processing_functions.h"
#include <limits>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Sample::Sample(){}
Sample::~Sample(){}


//************************************
// Method:    Sample
// FullName:  Sample::Sample
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: cv::Mat depth_image
// Parameter: nite::Skeleton skeleton
//************************************
Sample::Sample(cv::Mat &depth_image, nite::Skeleton &skeleton)
{
	depth_ = depth_image;
	skeleton_ = skeleton;
	RemoveDepthNoise(depth_);

	// ---------------------------------------------------------------------------------
	// Separate upper and lower part, shift to the centre
	if (countNonZero(depth_))
	{
		// Extract upper and lower body
		depth_upper_ = GetUpperBody(depth_);
		depth_lower_ = GetLowerBody(depth_);

		// Shift to the centre
		depth_upper_shifted_ = CenterImg(depth_upper_);
		depth_lower_shifted_ = CenterImg(depth_lower_);
	}
	else
	{
		depth_upper_ = depth_upper_shifted_ = depth_.clone();
		depth_lower_ = depth_lower_shifted_ = depth_.clone();
	}

	// ---------------------------------------------------------------------------------
	// Get projection of depth frames
	std::vector<cv::Mat> proj = Project(depth_);
	std::vector<cv::Mat> proj_upper_shifted = Project(depth_upper_shifted_);
	std::vector<cv::Mat> proj_lower_shifted = Project(depth_lower_shifted_);

	proj_X_ = proj[0];
	proj_Y_ = proj[1];
	proj_Z_ = proj[2];

	proj_upper_shifted_X_ = proj_upper_shifted[0];
	proj_upper_shifted_Y_ = proj_upper_shifted[1];
	proj_upper_shifted_Z_ = proj_upper_shifted[2];

	proj_lower_shifted_X_ = proj_lower_shifted[0];
	proj_lower_shifted_Y_ = proj_lower_shifted[1];
	proj_lower_shifted_Z_ = proj_lower_shifted[2];
}


//************************************
// Method:    RemoveDepthNoise
// FullName:  RemoveDepthNoise
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: cv::Mat & mat
//************************************
void Sample::RemoveDepthNoise(cv::Mat &mat)
{
	const int kDepthMax = 50000;
	for (size_t r = 0; r < mat.rows; r++)
	{
		for (size_t c = 0; c < mat.cols; c++)
		{
			if (mat.at<uint16_t>(r, c) > kDepthMax)
				mat.at<uint16_t>(r, c) = 0;
		}
	}
}


//************************************
// Method:    GetUpperBody
// FullName:  GetUpperBody
// Access:    public 
// Returns:   cv::Mat
// Qualifier:
// Parameter: cv::Mat & input_frame
//************************************
cv::Mat Sample::GetUpperBody(cv::Mat &input_frame)
{
	const double kRatio = 0.5;
	Rect rectBound = ImgProcessingFunctions::BoundingBox(input_frame);
	Rect rectLow(rectBound);
	rectLow.y = rectBound.y + rectBound.height * kRatio;
	rectLow.height = rectBound.height * (1 - kRatio);
	cv::Mat matUpper = input_frame.clone();
	matUpper(rectLow) = 0;
	return matUpper;
}


//************************************
// Method:    GetLowerBody
// FullName:  GetLowerBody
// Access:    public 
// Returns:   cv::Mat
// Qualifier:
// Parameter: cv::Mat & input_frame
//************************************
cv::Mat Sample::GetLowerBody(cv::Mat &input_frame)
{
	double kRatio = 0.5;
	Rect rectBound = ImgProcessingFunctions::BoundingBox(input_frame);
	Rect rectUp(rectBound);
	rectUp.height = rectBound.height * (1 - kRatio);
	cv::Mat matLower = input_frame.clone();
	matLower(rectUp) = 0;
	return matLower;
}


//************************************
// Method:    CenterImg
// FullName:  CenterImg
// Access:    public 
// Returns:   cv::Mat
// Qualifier:
// Parameter: cv::Mat & input_frame
//************************************
cv::Mat Sample::CenterImg(cv::Mat &input_frame)
{
	const int kDepthMax = 50000;

	// Find centre of input img
	cv::Point3f centre(0, 0, 0);
	int iCount = 0;
	for (size_t r = 0; r < input_frame.rows; r++)
	{
		for (size_t c = 0; c < input_frame.cols; c++)
		{
			uint16_t value = input_frame.at<uint16_t>(r, c);
			if (value > 0)
			{
				centre.x += c;
				centre.y += r;
				centre.z += value;
				iCount++;
			}
		}
	}
	centre.x = centre.x / iCount;
	centre.y = centre.y / iCount;
	centre.z = centre.z / iCount;

	// Shift the img
	cv::Point3f pCentreFrame(input_frame.cols / 2, input_frame.rows / 2, kDepthMax / 2);
	cv::Point3f pShift = pCentreFrame - centre;
	cv::Mat matShifted = cv::Mat::zeros(input_frame.size(), input_frame.type());
	for (size_t r = 0; r < input_frame.rows; r++)
	{
		for (size_t c = 0; c < input_frame.cols; c++)
		{
			uint16_t value = input_frame.at<uint16_t>(r, c);
			if (value > 0)
			{
				cv::Point3i newPos(0, 0, 0);
				newPos.x = c + pShift.x;
				newPos.y = r + pShift.y;
				newPos.z = value + pShift.z;
				if (newPos.x >= 0 && newPos.x < input_frame.cols
					&& newPos.y >= 0 && newPos.y < input_frame.rows)
				{
					matShifted.at<uint16_t>(newPos.y, newPos.x) = newPos.z;
				}
			}
		}
	}

	return matShifted;
}


//************************************
// Method:    Project
// FullName:  Project
// Access:    public 
// Returns:   cv::Mat*
// Qualifier:
// Parameter: Mat & input_frame
//************************************
std::vector<cv::Mat> Sample::Project(Mat &input_frame)
{
	const int kDepthMax = 50000;
	Mat matX, matY, matZ;

	const int iHeight = input_frame.size().height;
	const int iWidth = input_frame.size().width;
	const int iDepth = kDepthMax / 100;
	matX = Mat(iHeight, iDepth, CV_16U) = cv::Scalar(0, 0, 0);
	matY = Mat(iDepth, iWidth, CV_16U) = cv::Scalar(0, 0, 0);
	matZ = Mat(iHeight, iWidth, CV_16U) = cv::Scalar(0, 0, 0);

	for (size_t h = 0; h < iHeight; h++)
	{
		for (size_t w = 0; w < iWidth; w++)
		{
			uint16_t value = input_frame.at<uint16_t>(h, w);
			if (value > 0)
			{
				matZ.at<uint16_t>(h, w) = value;
				matX.at<uint16_t>(h, value / 100) = 65535;
				matY.at<uint16_t>(value / 100, w) = 65535;
			}
		}
	}

	std::vector<cv::Mat> result;
	result.push_back(matX);
	result.push_back(matY);
	result.push_back(matZ);
	return result;
}

