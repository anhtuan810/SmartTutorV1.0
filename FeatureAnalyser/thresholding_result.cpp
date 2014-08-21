//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "thresholding_result.h"

ThresholdingResult::ThresholdingResult(){}
ThresholdingResult::~ThresholdingResult(){}


void ThresholdingResult::AddCodewordBinary(std::vector<bool> &cw_binary)
{
	codeword_binaries_.push_back(cw_binary);
}


std::vector<bool> ThresholdingResult::GetCodewordBinary(const Codewords &codeword)
{
	return codeword_binaries_[codeword];
}

