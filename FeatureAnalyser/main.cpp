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
	feature_analyser.ReadFeatures_FromFiles(
		"C:\\contraction.txt",
		"C:\\stability.txt",
		"C:\\energy.txt",
		"C:\\direction.txt",
		"C:\\impulse.txt",
		"C:\\displacement.txt");

	Thresholds thresholds;
	ThresholdingResult thresholding_result = feature_analyser.ApplyThreshold(thresholds);
	AssessmentOverall assessment;
	assessment.PerformAssessment(thresholding_result);
	double a = assessment.GetScore_Contraction();
	double b = assessment.GetScore_Stability();
	double c = assessment.GetScore_Overarll();

}