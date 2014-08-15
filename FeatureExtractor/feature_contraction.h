//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATUTE_CONTRACTION_H_
#define FEATUTE_CONTRACTION_H_

#include <opencv2/core/core.hpp>
#include "sample.h"

class FeatureContraction
{
public:
	FeatureContraction();
	~FeatureContraction();
	double GetContraction(Sample &sample);
protected:
private:
};

#endif