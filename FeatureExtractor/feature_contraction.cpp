//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_contraction.h"
#include "img_processing_functions.h"

FeatureContraction::FeatureContraction(){}
FeatureContraction::~FeatureContraction(){}


//************************************
// Method:    GetContraction
// FullName:  FeatureContraction::GetContraction
// Access:    public 
// Returns:   double
// Qualifier:
// Parameter: Sample & sample
//************************************
double FeatureContraction::GetContraction(Sample &sample)
{
	double contraction = 0;

	int szX = cv::countNonZero(sample.proj_upper_shifted_X_);
	int szY = cv::countNonZero(sample.proj_upper_shifted_Y_);
	int szZ = cv::countNonZero(sample.proj_upper_shifted_Z_);

	if (szX > 0 && szY > 0 && szZ > 0)
	{
		//cv::Mat matBinaryX = ImgProcessing::Binarise(m_sample.ProjLowShiftedX, (uint16_t)0);
		//cv::Rect boundX = ImgProcessing::BoundingBox_LargestContour(matBinaryX);

		//cv::Mat matBinaryY = ImgProcessing::Binarise(m_sample.ProjLowShiftedY, (uint16_t)0);
		//cv::Rect boundY = ImgProcessing::BoundingBox_LargestContour(matBinaryY);

		cv::Mat depth_binary_Z = ImgProcessingFunctions::Binarise(sample.proj_lower_shifted_Z_, (uint16_t)0);
		cv::Rect bounding_box_Z = ImgProcessingFunctions::BoundingBox_LargestContour(depth_binary_Z);

		//float contrX = (float)boundX.size().area() / szX;
		//float contrY = (float)boundY.size().area() / szY;
		float contr_Z = (float)bounding_box_Z.size().area() / szZ;

		//this->Contraction = std::sqrt(contrX * contrX + contrY * contrY + contrZ * contrZ);

		////this->Contraction = contrZ;

		// Minimum contraction is 1
		//this->Contraction -= 1;

		contraction = contr_Z;
	}

	return contraction;
}
