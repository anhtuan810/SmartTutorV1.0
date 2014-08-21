//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_analyser.h"
#include <fstream>
#include <string>

using namespace std;

FeatureAnalyser::FeatureAnalyser(){}
FeatureAnalyser::~FeatureAnalyser(){}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAnalyser::ReadFeatures(
	std::vector<double> &feature_contraction, 
	std::vector<double> &feature_stability, 
	std::vector<double> &feature_energy, 
	std::vector<double> &feature_direction, 
	std::vector<double> &feature_impulse, 
	std::vector<double> &feature_displacement)
{
	feature_contraction_ = feature_contraction;
	feature_stability_ = feature_stability;
	feature_energy_ = feature_energy;
	feature_direction_ = feature_direction;
	feature_impulse_ = feature_impulse;
	feature_displacement_ = feature_displacement;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureAnalyser::ReadFeatures_FromFiles(
	char* file_contraction, 
	char* file_stability, 
	char* file_energy, 
	char* file_direction, 
	char* file_impulse, 
	char* file_displacement)
{
	feature_contraction_ = Read_One_File(file_contraction);
	feature_stability_ = Read_One_File(file_stability);
	feature_energy_ = Read_One_File(file_energy);
	feature_direction_ = Read_One_File(file_direction);
	feature_impulse_ = Read_One_File(file_impulse);
	feature_displacement_ = Read_One_File(file_displacement);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> FeatureAnalyser::Read_One_File(char* file_name)
{
	vector<double> feature;
	ifstream reader(file_name);
	string line;
	while (getline(reader, line))
	{
		feature.push_back(atof(line.c_str()));
	}
	reader.close();
	return feature;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
ThresholdingResult FeatureAnalyser::ApplyThreshold(Thresholds &threshold)
{
	ThresholdingResult result;
	const int kCodebookSize = 14;
	std::vector<double> features_list[kCodebookSize] = {
		feature_contraction_, feature_contraction_, feature_contraction_,
		feature_direction_, feature_direction_,
		feature_displacement_, feature_displacement_, 
		feature_energy_, feature_energy_, feature_energy_,
		feature_impulse_,
		feature_stability_, feature_stability_, feature_stability_};

	for (int i = Codewords(0); i < Codewords(kCodebookSize); ++i)
	{
		std::vector<bool> binary = Threshold_One_Feature(threshold.GetThresholds(Codewords(i)), features_list[i]);
		result.AddCodewordBinary(binary);
	}
	return result;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<bool> FeatureAnalyser::Threshold_One_Feature(std::pair<double, double> &thres, std::vector<double> &feature)
{
	std::vector<bool> result;
	for (size_t i = 0; i < feature.size(); i++)
	{
		if (feature[i] > thres.first && feature[i] < thres.second)
			result.push_back(true);
		else
			result.push_back(false);
	}
	return result;
}


