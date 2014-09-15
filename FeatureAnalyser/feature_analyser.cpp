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
void FeatureAnalyser::ReadFeatures_FromFiles(std::string data_folder)
{
	feature_contraction_ = ReadOneFile(data_folder + "contraction.txt");
	feature_stability_ = ReadOneFile(data_folder + "stability.txt");
	feature_energy_ = ReadOneFile(data_folder + "energy.txt");
	feature_direction_ = ReadOneFile(data_folder + "direction.txt");
	feature_impulse_ = ReadOneFile(data_folder + "impulse.txt");
	feature_displacement_ = ReadOneFile(data_folder + "displacement.txt");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> FeatureAnalyser::ReadOneFile(std::string file_name)
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
		std::vector<bool> binary = ThresholdOneFeature(threshold.GetThresholds(Codewords(i)), features_list[i]);
		result.AddCodewordBinary(binary);
	}
	return result;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<bool> FeatureAnalyser::ThresholdOneFeature(std::pair<double, double> &thres, std::vector<double> &feature)
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


void FeatureAnalyser::SmoothThresholdingResult(ThresholdingResult &original_result)
{
	
}


void FeatureAnalyser::SmoothOneBinaryArray(std::vector<bool> &input_array)
{
	cons
}


