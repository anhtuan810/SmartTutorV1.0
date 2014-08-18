//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_ENERGY_H_
#define FEATURE_ENERGY_H_

#include <vector>
#include "sample.h"

class FeatureEnergy
{
public:
	FeatureEnergy();
	~FeatureEnergy();
	double GetEnergy(Sample &sample);

protected:
private:
	std::vector<Sample> buffer_;
};

#endif