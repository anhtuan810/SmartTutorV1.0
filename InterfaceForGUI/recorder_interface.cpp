//
//  Smart Tutor v1.0
//	InterfaceForGUI
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "recorder_interface.h"
#include "sensor_kinect.h"
#include <string>
#include "oni_reader.h"
#include "feature_extractor.h"
#include "feature_analyser.h"
#include "thresholds_n_codewords.h"
#include "assessment_overall.h"


SensorKinect sensor_;

bool IStartRecordingONI(char* file_name)
{
	return sensor_.StartRecordingOrDie(file_name);
}

void IStopRecordingONI()
{
	sensor_.StopRecording();
}

bool ITurnOnKinectSensor()
{
	return sensor_.TurnOnOrDie();
}

void ITurnOffKinectSensor()
{
	sensor_.TurnOff();
}

char* IGrabFrame()
{
	return sensor_.GrabFrame();
}




FeatureAnalyser feature_analyser_;
AssessmentOverall scorer_;

bool IGenerateFeaturesFromONI(char* ONI_file_name, char* data_folder)
{
	ONIReader reader;
	reader.ReadONI(ONI_file_name);
	FeatureExtractor feature_extractor;
	feature_extractor.ReceiveONIReader_n_Process(reader.depth_user_frames_, reader.skeletons_, reader.user_tracked_, reader.frame_no_);
	feature_extractor.Save_2_Files(data_folder);
	return true;
}


void IPerformFeatureAnalysis(char* data_folder)
{
	//feature_analyser_.ReadFeatures_FromFiles(data_folder);
	//Thresholds threshold;
	//ThresholdingResult thresholding_result = feature_analyser_.ApplyThreshold(threshold);
	//scorer_.PerformAssessment(thresholding_result);
}

double* IGetFeatureScores()
{
	double scores[7] = { 0, 0, 0, 0, 0, 0, 0 };
	scores[0] = scorer_.GetScore_Contraction();
	scores[1] = scorer_.GetScore_Direction();
	scores[2] = scorer_.GetScore_Displacement();
	scores[3] = scorer_.GetScore_Energy();
	scores[4] = scorer_.GetScore_Impulse();
	scores[5] = scorer_.GetScore_Stability();
	scores[6] = scorer_.GetScore_Overarll();
	return scores;
}