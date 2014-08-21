//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "oni_reader.h"
#include "feature_extractor.h"
#include <iostream>

void main()
{
	ONIReader reader;
	reader.ReadONI("D:\\Data for Development\\ONI\\131.oni");
	FeatureExtractor feature_manager;
	feature_manager.ReceiveONIReader_n_Process(reader.depth_user_frames_, reader.skeletons_, reader.user_tracked_, reader.frame_no_);
	for (size_t i = 0; i < feature_manager.frame_no_; i++)
	{
		std::cout << feature_manager.feature_direction_[i] << "\n";
	}

	// Save to file
	feature_manager.Save_2_Files("C:\\");
}