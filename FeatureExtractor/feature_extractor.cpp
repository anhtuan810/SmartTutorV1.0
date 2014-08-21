//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//	- 2014.08.20: Added the Save_To_Files function 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_extractor.h"
#include "sample.h"
#include "feature_contraction.h"
#include "feature_stability.h"
#include "feature_energy.h"
#include "feature_impulse.h"
#include "feature_direction.h"
#include "feature_displacement.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

FeatureExtractor::FeatureExtractor(){}
FeatureExtractor::~FeatureExtractor(){}

/////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureExtractor::ReceiveONIReader_n_Process(
	std::vector<cv::Mat> depth_frames, 
	std::vector<nite::Skeleton> skeletons, 
	std::vector<bool> user_tracked, 
	const int frame_no)
{
	frame_no_ = frame_no;
	FeatureContraction contraction_extractor;
	FeatureStability stability_extractor;
	FeatureEnergy energy_extractor;
	FeatureDirection direction_extractor;
	FeatureImpulse impulse_extractor;
	FeatureDisplacement displacement_extractor;

	for (size_t i = 0; i < frame_no; i++)
	{
		double contraction = 0, stability = 0, energy = 0, direction = 0, displacement = 0;
		std::vector<double> impulse_list;

		if (user_tracked[i])
		{
			std::cout << i << "tracked \n";
			cv::Mat frm = depth_frames[i];
			nite::Skeleton skel = skeletons[i];

			Sample sample(frm, skel);
			contraction = contraction_extractor.GetContraction(sample);	
			stability = stability_extractor.GetStability(sample);
			energy = energy_extractor.GetEnergy(sample);
			direction = direction_extractor.GetDirection(sample);
			displacement = displacement_extractor.GetDisplacement(sample);
		}
		feature_contraction_.push_back(contraction);
		feature_stability_.push_back(stability);
		feature_energy_.push_back(energy);
		feature_direction_.push_back(direction);
		feature_displacement_.push_back(displacement);
	}

	// Impulse only computed in the end, after everything is completed
	feature_impulse_ = impulse_extractor.GetImpulseList(feature_energy_);
}



/////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureExtractor::Save_2_Files(char* folder_path)
{
	Save_One_Feature_2_File(std::string(folder_path) + "contraction.txt", feature_contraction_);
	Save_One_Feature_2_File(std::string(folder_path) + "direction.txt", feature_direction_);
	Save_One_Feature_2_File(std::string(folder_path) + "displacement.txt", feature_displacement_);
	Save_One_Feature_2_File(std::string(folder_path) + "energy.txt", feature_energy_);
	Save_One_Feature_2_File(std::string(folder_path) + "impulse.txt", feature_impulse_);
	Save_One_Feature_2_File(std::string(folder_path) + "stability.txt", feature_stability_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureExtractor::Save_One_Feature_2_File(std::string file_name, std::vector<double> feature)
{
	std::ofstream writer(file_name);
	for (size_t i = 0; i < feature.size(); ++i)
	{
		writer << feature[i] << "\n";
	}
	writer.close();
}
