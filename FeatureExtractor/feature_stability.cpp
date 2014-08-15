#include "feature_stability.h"
#include "img_processing_functions.h"

using namespace cv;

FeatureStability::FeatureStability(){}
FeatureStability::~FeatureStability(){}


//************************************
// Method:    GetStability
// FullName:  FeatureStability::GetStability
// Access:    public 
// Returns:   double
// Qualifier:
// Parameter: Sample & sample
//************************************
double FeatureStability::GetStability(Sample &sample)
{
	cv::Mat ground_projected = GetProjectedFrame(sample);
	cv::Point weight_centre = GetWeightCenter(ground_projected);
	cv::Rect foot_bounding_box = GetFootBoundingBox(sample, ground_projected);

	if (foot_bounding_box.width == 0)
		return 0;

	int d1 = (weight_centre.x - foot_bounding_box.x);
	int d2 = abs(weight_centre.x - (foot_bounding_box.x + foot_bounding_box.width));
	int delta = abs(d1 - d2);

	double Stability = (double)(weight_centre.x - foot_bounding_box.x) / foot_bounding_box.width;
	Stability -= 0.5;
	return Stability;
}


//************************************
// Method:    GetProjectedFrame
// FullName:  FeatureStability::GetProjectedFrame
// Access:    private 
// Returns:   cv::Mat
// Qualifier:
// Parameter: Sample & sample
//************************************
cv::Mat FeatureStability::GetProjectedFrame(Sample &sample)
{
	Mat proj_Z = sample.proj_Z_;

	const int kWidth = proj_Z.size().width;
	const int kHeight = proj_Z.size().height;
	cv::Mat result = cv::Mat(500, kWidth, CV_32FC1);
	result = cv::Scalar(0, 0, 0);

	// Get minY, maxY based on the bounding box
	// Processing in real-world coordinate, vertically inverts with image coordinate
	cv::Rect rect = ImgProcessingFunctions::BoundingBox(ImgProcessingFunctions::Binarise(proj_Z, (uint16_t)0));

	for (int h = 0; h < kHeight; h++)
	{
		for (int w = 0; w < kWidth; w++)
		{
			if (proj_Z.at<uint16_t>(h, w) != 0)
			{
				// Temporarily set height as height of the frame, will change later
				// Value of the point based on its height
				float value = (float)(h - rect.y) / rect.height;
				// depth ID
				int depth_id = proj_Z.at<uint16_t>(h, w) / 100;
				result.at<float>(depth_id, w) += value;
			}
		}
	}
	return result;
}



//************************************
// Method:    GetWeightCenter
// FullName:  FeatureStability::GetWeightCenter
// Access:    private 
// Returns:   cv::Point
// Qualifier:
// Parameter: cv::Mat & ground_projected
//************************************
cv::Point FeatureStability::GetWeightCenter(cv::Mat &ground_projected)
{
	double sum_value = ImgProcessingFunctions::SumMat(ground_projected, (float)0);
	if (sum_value <= 0)
		return cv::Point(0, 0);

	cv::Mat binary_mat = ImgProcessingFunctions::Binarise(ground_projected, (float)0);
	cv::Rect bounding_box = ImgProcessingFunctions::BoundingBox(binary_mat);
	cv::Mat user_ROI = ground_projected(bounding_box);

	// Move horizontally
	int x = -1;
	int i = 0;
	double sum = 0;
	while (i < user_ROI.size().width - 1 && x == -1)
	{
		sum += ImgProcessingFunctions::SumMat(user_ROI.col(i), (float)0);
		if (sum > sum_value / 2)
			x = i;
		i++;
	}

	// Move vertically
	int y = -1;
	i = 0;
	sum = 0;
	while (i < user_ROI.size().height - 1 && y == -1)
	{
		sum += ImgProcessingFunctions::SumMat(user_ROI.row(i), (float)0);
		if (sum > sum_value / 2)
			y = i;
		i++;
	}

	cv::Point weight_centre = cv::Point(bounding_box.x + x, bounding_box.y + y);
	return weight_centre;

	//// Draw the point on UserProjected Image
	//cv::RotatedRect circle = cv::RotatedRect(cv::Point(rctBoundingBox.x + x, rctBoundingBox.y + y), cv::Size2f(5, 5), 0);
	//cv::ellipse(this->GroundProjected, circle, cv::Scalar(0, 0, 0), 2, 8);
}


//************************************
// Method:    GetFootBoundingBox
// FullName:  FeatureStability::GetFootBoundingBox
// Access:    private 
// Returns:   cv::Rect
// Qualifier:
// Parameter: Sample & sample
// Parameter: cv::Mat & ground_projected
//************************************
cv::Rect FeatureStability::GetFootBoundingBox(Sample &sample, cv::Mat &ground_projected)
{
	const double kFootRatio = 0.2;

	// Get user ROI
	cv::Mat user_binary = ImgProcessingFunctions::Binarise(sample.proj_Z_, (uint16_t)0);
	cv::Rect user_bounding_box = ImgProcessingFunctions::BoundingBox(sample.proj_Z_);
	cv::Mat user_ROI = user_binary(user_bounding_box);

	// How much is enough to stop
	int area = cv::countNonZero(user_binary);
	int area_threshold = area * kFootRatio;

	// Start to MOVE (inside the ROI)
	int pos = user_ROI.size().height - 1;
	int sum = 0;
	while (pos >= 0 && sum < area_threshold)
	{
		sum += ImgProcessingFunctions::SumMat(user_ROI.row(pos), (uchar)0);
		pos--;
	}

	// If cannot find the line
	if (pos == -1)
		return cv::Rect(0, 0, 0, 0);

	// Get the bounding box that covers foot, on ProjectedUser
	cv::Mat user_row_ROI = user_ROI.row(pos);
	cv::Point top_left;
	cv::Size box_size;

	// Move left --> right
	bool found = false;
	int i = 0;
	while (!found)
	{
		if (user_row_ROI.at<uchar>(0, i) > 0)
			found = true;
		i++;
	}
	top_left.x = i;

	// Move right --> left
	found = false;
	i = user_row_ROI.size().width - 1;
	while (!found)
	{
		if (user_row_ROI.at<uchar>(0, i) > 0)
			found = true;
		i--;
	}
	box_size.width = i - top_left.x;

	//-----------------------------------------------------------------------------------------------------
	// Get min and max of the row to set vertical limits of the box
	cv::Mat user_ROI_Z = sample.proj_Z_(user_bounding_box);
	cv::Mat user_ROI_Z_row = user_ROI_Z.row(pos);
	int min = 100000;
	int max = 0;
	for (int k = 0; k < user_ROI_Z_row.size().width; k++)
	{
		if (user_ROI_Z_row.at<__int16>(0, k) <= 0)
			continue;

		if (user_ROI_Z_row.at<__int16>(0, k) > max)
		{
			max = user_ROI_Z_row.at<__int16>(0, k);
		}
		if (user_ROI_Z_row.at<__int16>(0, k) < min)
		{
			min = user_ROI_Z_row.at<__int16>(0, k);
		}
	}
	top_left.y = (int)min;
	box_size.height = (int)(max - min);

	// Convert the bounding box to fit with ProjectedUser
	cv::Rect foot_bounding_box = cv::Rect(top_left.x + user_bounding_box.x, top_left.y + user_bounding_box.y, box_size.width, box_size.height);

	// Draw bounding box
	//cv::rectangle(ground_projected, FootBoundingBox, cv::Scalar(100000, 100000, 100000), 2);

	return foot_bounding_box;
}
