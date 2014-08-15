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