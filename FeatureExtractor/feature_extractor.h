//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_MANAGER_H_
#define FEATURE_MANAGER_H_

#include <opencv2/core/core.hpp>
#include <NiTE.h>
#include <vector>
#include <string>

class FeatureExtractor
{
public:
	FeatureExtractor();
	~FeatureExtractor();

	// Primary method, handles everything
	void ReceiveONIReader_n_Process(
		std::vector<cv::Mat> depth_frames, 
		std::vector<nite::Skeleton> skeletons, 
		std::vector<bool> user_tracked, 
		const int frame_no);

	// Save results to files for further processing (save time) or visualisation in GUI module
	void Save_2_Files(char* folder_path);

	int frame_no_;
	std::vector<double> feature_contraction_;
	std::vector<double> feature_stability_;
	std::vector<double> feature_energy_;
	std::vector<double> feature_direction_;
	std::vector<double> feature_impulse_;
	std::vector<double> feature_displacement_;

protected:
private:
	// Only to support the special treatment of impulse
	std::vector<double> energy_buffer_4_impulse_;

	// private, Support the Save_2_Files method
	void Save_One_Feature_2_File(std::string file_name, std::vector<double> feature);
};

#endif