//
//  Smart Tutor v1.0
//	InterfaceForGUI
//
//  Created: 2014.08.22
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

extern "C" { __declspec(dllexport) bool IGenerateFeaturesFromONI(char* ONI_file_name, char* data_folder); }
extern "C" { __declspec(dllexport) void IPerformFeatureAnalysis(char* data_folder); }
extern "C" { __declspec(dllexport) double* IGetFeatureScores(); }