//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "img_processing_functions.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;


//************************************
// Method:    MEI
// FullName:  ImgProcessingFunctions::MEI
// Access:    public static 
// Returns:   cv::Mat
// Qualifier:
// Parameter: vector<Mat> input
//************************************
Mat ImgProcessingFunctions::MEI(vector<Mat> input)
{
	if (input.size() < 1)
		return Mat(100, 100, CV_8U);

	int iHeight = input.at(0).size().height;
	int iWidth = input.at(0).size().width;
	int iSz = input.size();

	Mat matMEI(input.at(0).size(), CV_8U);
	for (int h = 0; h < iHeight; h++)
	{
		for (int w = 0; w < iWidth; w++)
		{
			matMEI.at<char>(h, w) = 0;
			double found = false;
			int i = 0;
			while (!found && i < input.size() - 1)
			{
				if (input.at(i).at<char>(h, w) != 0)
				{
					found = true;
					matMEI.at<char>(h, w) = 255;
				}
				if (found && input.at(input.size() - 1).at<char>(h, w) != 0)
				{
					matMEI.at<char>(h, w) = 0;
				}
				i++;
			}
		}
	}
	return matMEI;
}


//************************************
// Method:    MEI_int16
// FullName:  ImgProcessingFunctions::MEI_int16
// Access:    public static 
// Returns:   cv::Mat
// Qualifier:
// Parameter: vector<Mat> input
//************************************
Mat ImgProcessingFunctions::MEI_int16(vector<Mat> input)
{
	if (input.size() < 1)
		return Mat(100, 100, CV_16U);

	int iHeight = input.at(0).size().height;
	int iWidth = input.at(0).size().width;
	int iSz = input.size();

	Mat matMEI(input.at(0).size(), CV_16U);
	for (int h = 0; h < iHeight; h++)
	{
		for (int w = 0; w < iWidth; w++)
		{
			matMEI.at<__int16>(h, w) = 0;
			double found = false;
			int i = 0;
			while (!found && i < input.size() - 1)
			{
				if (input.at(i).at<__int16>(h, w) != 0)
				{
					found = true;
					matMEI.at<__int16>(h, w) = 255;
				}
				if (found && input.at(input.size() - 1).at<__int16>(h, w) != 0)
				{
					matMEI.at<__int16>(h, w) = 0;
				}
				i++;
			}
		}
	}
	return matMEI;
}


//************************************
// Method:    MHI
// FullName:  ImgProcessingFunctions::MHI
// Access:    public static 
// Returns:   cv::Mat
// Qualifier:
// Parameter: vector<Mat> input
//************************************
Mat ImgProcessingFunctions::MHI(vector<Mat> input)
{
	if (input.size() < 1)
		return Mat(100, 100, CV_8U);

	int iHeight = input.at(0).size().height;
	int iWidth = input.at(0).size().width;
	int iSz = input.size();

	Mat matMEI(input.at(0).size(), CV_8U);
	for (int h = 0; h < iHeight; h++)
	{
		for (int w = 0; w < iWidth; w++)
		{
			matMEI.at<char>(h, w) = 0;
			double found = false;
			int i = 0;
			while (!found && i < input.size() - 1)
			{
				if (input.at(i).at<char>(h, w) != 0)
				{
					found = true;
					matMEI.at<char>(h, w) = i;
				}
				if (found && input.at(input.size() - 1).at<char>(h, w) != 0)
				{
					matMEI.at<char>(h, w) = 0;
				}
				i++;
			}
		}
	}
	return matMEI;
}


//************************************
// Method:    BoundingBox
// FullName:  ImgProcessingFunctions::BoundingBox
// Access:    public static 
// Returns:   cv::Rect
// Qualifier:
// Parameter: cv::Mat binary_mat
//************************************
cv::Rect ImgProcessingFunctions::BoundingBox(cv::Mat binary_mat)
{
	cv::Rect rect;
	int minH = 0, maxH = 0, minW = 0, maxW = 0;

	// Find the minimum bounding box
	int height = binary_mat.size().height;
	int width = binary_mat.size().width;

	// Min H
	int h = 0;
	bool found = false;
	while (!found && h < height)
	{
		if (cv::countNonZero(binary_mat.row(h)) != 0)
			found = true;
		h++;
	}
	if (found)
		minH = h;

	// Max H
	h = height - 1;
	found = false;
	while (!found && h >= 0)
	{
		if (cv::countNonZero(binary_mat.row(h)) != 0)
			found = true;
		h--;
	}
	if (found)
		maxH = h;

	// Min W
	int w = 0;
	found = false;
	while (!found && w < width)
	{
		if (cv::countNonZero(binary_mat.col(w)) != 0)
			found = true;
		w++;
	}
	if (found)
		minW = w;

	// Max W
	w = width - 1;
	found = false;
	while (!found && w >= 0)
	{
		if (cv::countNonZero(binary_mat.col(w)) != 0)
			found = true;
		w--;
	}
	if (found)
		maxW = w;

	rect = cv::Rect(cv::Point(minW, minH), cv::Point(maxW, maxH));
	return rect;
}


//************************************
// Method:    BoundingBox_LargestContour
// FullName:  ImgProcessingFunctions::BoundingBox_LargestContour
// Access:    public static 
// Returns:   cv::Rect
// Qualifier:
// Parameter: cv::Mat binary_mat
//************************************
cv::Rect ImgProcessingFunctions::BoundingBox_LargestContour(cv::Mat binary_mat)
{
	vector<vector<Point> > contours;

	// Finds contours
	cv::Mat matOut;
	cv::findContours(binary_mat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	// Finds the contour with the largest area
	int area = 0;
	int idx;
	for (int i = 0; i < contours.size(); i++) {
		if (area < contours[i].size())
		{
			idx = i;
			area = contours[idx].size();
		}
	}

	// Calculates the bounding rect of the largest area contour
	cv::Rect rect = cv::boundingRect(contours[idx]);
	return rect;
}


//************************************
// Method:    ExtractUpperBody
// FullName:  ImgProcessingFunctions::ExtractUpperBody
// Access:    public static 
// Returns:   cv::Mat
// Qualifier:
// Parameter: cv::Mat input_frame
// Parameter: float ratio
//************************************
cv::Mat ImgProcessingFunctions::ExtractUpperBody(cv::Mat input_frame, float ratio)
{
	Rect rectBound = ImgProcessingFunctions::BoundingBox(input_frame);
	Rect rectLow(rectBound);
	rectLow.y = rectBound.y + rectBound.height * ratio;
	rectLow.height = rectBound.height * (1 - ratio);
	cv::Mat matUpper = input_frame.clone();
	matUpper(rectLow) = 0;
	return matUpper;
}
