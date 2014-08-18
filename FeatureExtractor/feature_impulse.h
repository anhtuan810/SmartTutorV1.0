//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include <vector>

class FeatureImpulse
{
public:
	FeatureImpulse();
	~FeatureImpulse();
	std::vector<double> GetImpulseList(std::vector<double> &energy_list);
protected:
private:
};