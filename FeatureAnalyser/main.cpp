//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "feature_analyser.h"
#include "thresholds_n_codewords.h"
#include "thresholding_result.h"
#include "assessment_overall.h"
#include <vector>

void main()
{
	FeatureAnalyser feature_analyser;
	feature_analyser.ReadFeatures_FromFiles("C:\\");

	Thresholds thresholds;
	ThresholdingResult thresholding_result = feature_analyser.ApplyThreshold(thresholds);
	AssessmentOverall assessment;
	assessment.PerformAssessment(thresholding_result);
	assessment.SaveResultToHDD("D:\\");

}