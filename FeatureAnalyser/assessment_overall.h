//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef ASSESSMENT_OVERALL_H_
#define ASSESSMENT_OVERALL_H_

#include "thresholding_result.h"

class AssessmentOverall
{
public:
	AssessmentOverall();
	~AssessmentOverall();
	double GetScore_Contraction();
	double GetScore_Direction();
	double GetScore_Displacement();
	double GetScore_Energy();
	double GetScore_Impulse();
	double GetScore_Stability();
	double GetScore_Overarll();

	// The major functions
	void PerformAssessment(ThresholdingResult &thresholding_result);
	// Assess result after performed
	double GetCodewordPercentage(Codewords codeword);
protected:
private:
	double score_overall_ = 0;
	double score_contraction_ = 0;
	double score_direction_ = 0;
	double score_displacement_ = 0;
	double score_energy_ = 0;
	double score_impulse_ = 0;
	double score_stability_ = 0;
	ThresholdingResult thresholding_result_;


	//-------------------------------------- PERCENTAGE ---------------------------------------------------
	// The percentage of codewords, number of component = number of codewords
	std::vector<double> percentage_codewords_;
	// private, Get the percentage of codewords in the same category
	void GetPercentage();
	// private, Just to support GetPercentage()
	double GetPercentage_OneBinary(std::vector<bool> &binary);


	//--------------------------------------- SCORING -----------------------------------------------------
	// Score of separated features based on (1) the binary distribution of codewords and (2) the percentage
	// Just the percentage right now
	void ScoreContraction();
	void ScoreDirection();
	void ScoreDisplacement();
	void ScoreEnergy();
	void ScoreImpulse();
	void ScoreStability();
	// private, The overall score from scores of features
	void ScoreOverall();
};

#endif