//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "assessment_overall.h"
#include "thresholds_n_codewords.h"
#include <math.h>

AssessmentOverall::AssessmentOverall(){}
AssessmentOverall::~AssessmentOverall(){}


// ---------------------- PUBLIC FUNCTIONS --------------------------------------------------------------------
#pragma region Public Functions

void AssessmentOverall::PerformAssessment(ThresholdingResult &thresholding_result)
{
	thresholding_result_ = thresholding_result;
	GetPercentage();

	ScoreContraction();
	ScoreDirection();
	ScoreDisplacement();
	ScoreEnergy();
	ScoreImpulse();	
	ScoreStability();
	ScoreOverall();
}

double AssessmentOverall::GetScore_Contraction() {	return score_contraction_; }
double AssessmentOverall::GetScore_Direction() { return score_direction_; }
double AssessmentOverall::GetScore_Displacement() { return score_displacement_; }
double AssessmentOverall::GetScore_Energy() { return score_energy_; }
double AssessmentOverall::GetScore_Impulse() { return score_impulse_; }
double AssessmentOverall::GetScore_Stability() { return score_stability_; }
double AssessmentOverall::GetScore_Overarll() { return score_overall_; }

#pragma endregion



// ----------------------- PERCENTAGE --------------------------------------------------------------------------
#pragma region Get percentage from binary of codewords, to support: (1) Scoring, (2) GUI

void AssessmentOverall::GetPercentage()
{
	const int kCodewordNo = 14;
	for (int i = 0; i <= kCodewordNo; ++i)
	{
		double percentage = GetPercentage_OneBinary(thresholding_result_.GetCodewordBinary(Codewords(i)));
		percentage_codewords_.push_back(percentage);
	}
}

double AssessmentOverall::GetPercentage_OneBinary(std::vector<bool> &binary)
{
	int count = 0;
	for (size_t i = 0; i < binary.size(); ++i)
	{
		if (binary[i]) count++;
	}
	return (double)count / binary.size();
}

double AssessmentOverall::GetCodewordPercentage(Codewords codeword)
{
	return percentage_codewords_[codeword];
}

#pragma endregion 



// ------------------------ SCORING ----------------------------------------------------------------------------
#pragma region Score each feature and the whole presentation based on: (1) Percentage, (2) Binary

void AssessmentOverall::ScoreContraction()
{
	double per_contr_low = GetCodewordPercentage(Codewords::CONTRACTION_LOW);
	double per_contr_average = GetCodewordPercentage(Codewords::CONTRACTION_AVERAGE);
	double per_contr_high = GetCodewordPercentage(Codewords::CONTRACTION_HIGH);

	// Start at 6
	double score = 6;
	// Decrease with low contraction
	score -= 4 * per_contr_low;
	// Increase with high contraction
	score += 6 * per_contr_high;

	score_contraction_ = score;
}

void AssessmentOverall::ScoreDirection()
{
	double per_forward = GetCodewordPercentage(Codewords::DIRECTION_FORWARD);
	double per_backward = GetCodewordPercentage(Codewords::DIRECTION_BACKWARD);
	
	double score = 6;
	score -= 12 * per_backward;
	score += 12 * per_forward;

	score_direction_ = score;
}

void AssessmentOverall::ScoreDisplacement()
{
	double per_move = GetCodewordPercentage(Codewords::DISPLACEMENT_MOVING);
	double per_not_move = GetCodewordPercentage(Codewords::DISPLACEMENT_NOT_MOVING);

	double score = 6;
	score += 4 * per_move;

	score_displacement_ = score;
}

void AssessmentOverall::ScoreEnergy()
{
	double per_energy_low = GetCodewordPercentage(Codewords::ENERGY_LOW);
	double per_energy_average = GetCodewordPercentage(Codewords::ENERGY_AVERAGE);
	double per_energy_high = GetCodewordPercentage(Codewords::ENERGY_HIGH);

	double score = 6;
	score -= 4 * per_energy_low;
	score -= 3 * per_energy_high;
	score += 6 * per_energy_average;

	score_energy_ = score;
}

void AssessmentOverall::ScoreImpulse()
{
	double per_impulse = GetCodewordPercentage(Codewords::IMPULSE);

	double score = 6;
	score += per_impulse * 4;

	score_impulse_ = score;
}

void AssessmentOverall::ScoreStability()
{
	double per_left = GetCodewordPercentage(Codewords::STABILITY_LEAN_LEFT);
	double per_right = GetCodewordPercentage(Codewords::STABILITY_LEAN_RIGHT);
	double per_balanced = GetCodewordPercentage(Codewords::STABILITY_BALANCED);

	double score = 6;
	score += 4 * per_balanced;
	score -= 3 * per_left;
	score -= 3 * per_right;

	score_stability_ = score;
}

void AssessmentOverall::ScoreOverall()
{
	double score = 0;
	score = (score_contraction_ + score_direction_ + score_displacement_ + score_energy_ + score_impulse_ + score_stability_) / 6;
	score_overall_ = score;
}

#pragma endregion
