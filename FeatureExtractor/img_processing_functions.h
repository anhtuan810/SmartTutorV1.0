//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef IMG_PROCESSING_FUNCTIONS_H_
#define IMG_PROCESSING_FUNCTIONS_H_

#include <opencv2\core\core.hpp>

class ImgProcessingFunctions
{
public:
	static cv::Mat MEI(std::vector<cv::Mat> input);

	static cv::Mat MEI_int16(std::vector<cv::Mat> input);

	static cv::Mat MHI(std::vector<cv::Mat> input);


	// Get bounding box manually for the whole scene
	// No need binarisation in advance
	static cv::Rect BoundingBox(cv::Mat matAnyType);


	// Bounding box of the largest contour
	// Eliminate the noise in Contraction if using full bounding box
	static cv::Rect BoundingBox_LargestContour(cv::Mat matBinary);


	// Extract upper body based on ratio
	static cv::Mat ExtractUpperBody(cv::Mat inputImg, float ratio);


	// Template function must be defined entirely in the header, otherwise there will be a linker error
	template <typename TYPE>
	static TYPE SumMat(cv::Mat mat, TYPE type)
	{
		TYPE sum = 0;
		for (size_t r = 0; r < mat.rows; r++)
		{
			for (size_t c = 0; c < mat.cols; c++)
			{
				sum += mat.at<TYPE>(r, c);
			}
		}
		return sum;
	};


	// Binarise, mostly for user map and before getting bounding box
	template <typename TYPE>
	static cv::Mat Binarise(cv::Mat mat, TYPE type)
	{
		cv::Mat matOut(mat.size(), CV_8UC1);
		matOut = cv::Scalar(0, 0, 0);

		for (int h = 0; h < matOut.rows; h++)
		{
			for (int w = 0; w < matOut.cols; w++)
			{
				if (mat.at<TYPE>(h, w) > 0)
					matOut.at<uchar>(h, w) = 255;
				else
					matOut.at<uchar>(h, w) = 0;
			}
		}
		return matOut;
	};

	cv::Mat Dilation(cv::Mat &input);
};

#endif