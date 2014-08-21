//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#ifndef THRESHOLDING_RESULT_H_
#define THRESHOLDING_RESULT_H_

#include <vector>
#include "thresholds_n_codewords.h"

class ThresholdingResult
{
public:
	ThresholdingResult();
	~ThresholdingResult();

	// Add the binary result of thresholding one feature
	// Number of items = Number of codewords (14)
	void AddCodewordBinary(std::vector<bool> &cw_binary);

	// Get result, based on codeword for saving lines of code
	std::vector<bool> GetCodewordBinary(const Codewords &codeword);
protected:
private:
	std::vector<std::vector<bool>> codeword_binaries_;
};

#endif