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
#include <fstream>

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
	for (int i = 0; i < kCodewordNo; ++i)
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


std::vector<bool> AssessmentOverall::GetCodewordBinary(Codewords codeword)
{
	return thresholding_result_.GetCodewordBinary(codeword);
}

#pragma endregion



// ------------------------ SAVE RESULT ----------------------------------------------------------------------------
#pragma region Save result to HDD

void AssessmentOverall::SaveResultToHDD(std::string data_folder)
{
	SaveAllScore(data_folder + "scores.txt");

	SaveOneCodewordBinary(GetCodewordBinary(Codewords::CONTRACTION_HIGH), data_folder + "binary_contraction_high.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::CONTRACTION_AVERAGE), data_folder + "binary_contraction_average.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::CONTRACTION_LOW), data_folder + "binary_contraction_low.txt");

	SaveOneCodewordBinary(GetCodewordBinary(Codewords::DIRECTION_BACKWARD), data_folder + "binary_direction_backward.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::DIRECTION_FORWARD), data_folder + "binary_direction_forward.txt");

	SaveOneCodewordBinary(GetCodewordBinary(Codewords::DISPLACEMENT_MOVING), data_folder + "binary_displacement_moving.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::DISPLACEMENT_MOVING), data_folder + "binary_displacement_not_moving.txt");

	SaveOneCodewordBinary(GetCodewordBinary(Codewords::ENERGY_HIGH), data_folder + "binary_energy_high.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::ENERGY_AVERAGE), data_folder + "binary_energy_average.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::ENERGY_LOW), data_folder + "binary_energy_low.txt");

	SaveOneCodewordBinary(GetCodewordBinary(Codewords::IMPULSE), data_folder + "binary_impulse.txt");

	SaveOneCodewordBinary(GetCodewordBinary(Codewords::STABILITY_LEAN_LEFT), data_folder + "binary_lean_left.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::STABILITY_LEAN_RIGHT), data_folder + "binary_lean_right.txt");
	SaveOneCodewordBinary(GetCodewordBinary(Codewords::STABILITY_BALANCED), data_folder + "binary_balanced.txt");
}


void AssessmentOverall::SaveAllScore(std::string file_name)
{
	std::ofstream writer(file_name);
	writer << score_overall_ << "\n";
	writer << score_contraction_ << "\n";
	writer << score_direction_ << "\n";
	writer << score_displacement_ << "\n";
	writer << score_energy_ << "\n";
	writer << score_impulse_ << "\n";
	writer << score_stability_ << "\n";
	writer.close();
}


void AssessmentOverall::SaveOneCodewordBinary(std::vector<bool> &binary_data, std::string file_name)
{
	std::ofstream writer(file_name);
	for (size_t i = 0; i < binary_data.size(); i++)
	{
		if (binary_data[i])
			writer << "1" << "\n";
		else
			writer << "0" << "\n";
	}
	writer.close();
}

#pragma endregion


