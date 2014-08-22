//
//  Smart Tutor v1.0
//	Feature Analyser
//	The primary class of the module, cover everything
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_ANALYSER_H_
#define FEATURE_ANALYSER_H_

#include <vector>
#include <string>
#include "thresholds_n_codewords.h"
#include "thresholding_result.h"

class FeatureAnalyser
{
public:
	FeatureAnalyser();
	~FeatureAnalyser();

	// Push data directly as vectors, read from FeatureExtractor
	void ReadFeatures(
		std::vector<double> &feature_contraction,
		std::vector<double> &feature_stability,
		std::vector<double> &feature_energy,
		std::vector<double> &feature_direction,
		std::vector<double> &feature_impulse,
		std::vector<double> &feature_displacement);

	// Read features from *.txt files that are generated from FeatureExtractor module
	void ReadFeatures_FromFiles(std::string data_folder);

	// Thresholding the whole feature values
	ThresholdingResult ApplyThreshold(Thresholds &threshold);
protected:
private:
	std::vector<double> feature_contraction_;
	std::vector<double> feature_stability_;
	std::vector<double> feature_energy_;
	std::vector<double> feature_direction_;
	std::vector<double> feature_impulse_;
	std::vector<double> feature_displacement_;

	// Private, read one single feature file
	std::vector<double> Read_One_File(std::string file_name);
	std::vector<bool> Threshold_One_Feature(std::pair<double, double> &thres, std::vector<double> &feature);
};

#endif